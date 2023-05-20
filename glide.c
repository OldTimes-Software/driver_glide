/**
 * Hei Platform Library
 * Copyright (C) 2017-2021 Mark E Sowden <hogsy@oldtimes-software.com>
 * This software is licensed under MIT. See LICENSE for more details.
 */

#include "plugin.h"

#if defined( _WIN32 )
#	include <windows.h>
#endif
#if defined( _MSC_VER ) || defined( __MINGW32__ )
#	define __MSC__
#endif
#include <glide.h>

/* TODO:
 *  - the initialize function via api does not pass in window handle, which it probably should
 *  - we don't have any ability to ensure our context is current right now because there's no
 *    'Start' and 'End' of when we're drawing anything, which could prove to be a problem if a
 *    user alt-tabs out and back in
 */

typedef struct GlideDrvRenderState {
	GrContext_t context;

	GrColor_t clearColour;
} GlideDrvRenderState;
static GlideDrvRenderState renderState;

static PLFunctionResult Initialize( void ) {
	memset( &renderState, 0, sizeof( GlideDrvRenderState ) );

	FxI32 numBoards;
	grGet( GR_NUM_BOARDS, sizeof( numBoards ), &numBoards );
	if ( numBoards <= 0 ) {
		gInterface->core->ReportError( PL_RESULT_GRAPHICSINIT,
		                               PL_FUNCTION,
		                               "no valid glide boards found" );
		return PL_RESULT_GRAPHICSINIT;
	}

	grGlideInit();
	grSstSelect( 0 );

	GrScreenResolution_t screenResolution = GR_RESOLUTION_NONE;
	GrScreenRefresh_t refresh = GR_REFRESH_NONE;

	/* the following fetches the active window, so we can determine
	 * the appropriate resolution and refresh rate to provide glide
	 * with.
	 * */

#if defined( _WIN32 )
	HWND hwnd = GetActiveWindow();
	if ( hwnd != NULL ) {
		RECT windowRect;
		if ( GetWindowRect( hwnd, &windowRect ) ) {
			if ( windowRect.right >= 1600 ) {
				screenResolution = GR_RESOLUTION_1600x1200;
			} else if ( windowRect.right >= 1280 ) {
				screenResolution = GR_RESOLUTION_1280x1024;
			} else if ( windowRect.right >= 1024 ) {
				screenResolution = GR_RESOLUTION_1024x768;
			} else if ( windowRect.right >= 800 ) {
				screenResolution = GR_RESOLUTION_800x600;
			} else if ( windowRect.right >= 640 ) {
				screenResolution = GR_RESOLUTION_640x480;
			} else if ( windowRect.right >= 320 ) {
				screenResolution = GR_RESOLUTION_320x240;
			} else {
				screenResolution = GR_RESOLUTION_NONE;
			}
		}

		DEVMODE devmode;
		if ( EnumDisplaySettings( NULL, ENUM_CURRENT_SETTINGS, &devmode ) ) {
			switch ( devmode.dmDisplayFrequency ) {
				case 60:
					refresh = GR_REFRESH_60Hz;
					break;
				case 70:
					refresh = GR_REFRESH_70Hz;
					break;
				case 72:
					refresh = GR_REFRESH_72Hz;
					break;
				case 75:
					refresh = GR_REFRESH_75Hz;
					break;
				case 80:
					refresh = GR_REFRESH_80Hz;
					break;
				case 85:
					refresh = GR_REFRESH_85Hz;
					break;
				case 90:
					refresh = GR_REFRESH_90Hz;
					break;
				case 100:
					refresh = GR_REFRESH_100Hz;
					break;
				case 120:
					refresh = GR_REFRESH_120Hz;
					break;
				default:
					break;
			}
		}
	}
#endif

	renderState.context = grSstWinOpen( 0,
	                                    screenResolution,
	                                    refresh,
	                                    GR_COLORFORMAT_RGBA,
	                                    GR_ORIGIN_UPPER_LEFT,
	                                    2, 1 );
	if ( renderState.context == 0 ) {
		gInterface->core->ReportError( PL_RESULT_GRAPHICSINIT, PL_FUNCTION, "failed to create glide context" );
		return PL_RESULT_GRAPHICSINIT;
	}

	/* describe our vertex layout for glide (it never changes) */
	grVertexLayout( GR_PARAM_XY, PL_OFFSETOF( PLGVertex, position.x ), GR_PARAM_ENABLE );
	grVertexLayout( GR_PARAM_Z, PL_OFFSETOF( PLGVertex, position.z ), GR_PARAM_ENABLE );
	grVertexLayout( GR_PARAM_RGB, PL_OFFSETOF( PLGVertex, colour ), GR_PARAM_ENABLE );
	grVertexLayout( GR_PARAM_ST0, PL_OFFSETOF( PLGVertex, st[ 0 ].x ), GR_PARAM_ENABLE );
	grVertexLayout( GR_PARAM_ST1, PL_OFFSETOF( PLGVertex, st[ 1 ].x ), GR_PARAM_ENABLE );
	grVertexLayout( GR_PARAM_ST2, PL_OFFSETOF( PLGVertex, st[ 2 ].x ), GR_PARAM_ENABLE );

	return PL_RESULT_SUCCESS;
}

static void Shutdown( void ) {
	if ( renderState.context != 0 ) {
		grSstWinClose( renderState.context );
		renderState.context = 0;
	}

	grGlideShutdown();
}

static bool SupportsHwShaders( void ) {
	return false;
}

static void GetMaxTextureUnits( unsigned int *i ) {
	grGet( GR_NUM_TMU, sizeof( FxI32 ), ( FxI32 * ) i );
}

static void GetMaxTextureSize( unsigned int *i ) {
	grGet( GR_MAX_TEXTURE_SIZE, sizeof( FxI32 ), ( FxI32 * ) i );
}

static GrAlphaBlendFnc_t ConvertPlgBlendToGlideBlend( PLGBlend blend ) {
	switch ( blend ) {
		default:
		case PLG_BLEND_ZERO:
			return GR_BLEND_ZERO;

		case PLG_BLEND_ONE:
			return GR_BLEND_ONE;

		case PLG_BLEND_SRC_COLOR:
			return GR_BLEND_SRC_COLOR;
		case PLG_BLEND_ONE_MINUS_SRC_COLOR:
			return GR_BLEND_ONE_MINUS_SRC_COLOR;

		case PLG_BLEND_SRC_ALPHA:
			return GR_BLEND_SRC_ALPHA;
		case PLG_BLEND_ONE_MINUS_SRC_ALPHA:
			return GR_BLEND_ONE_MINUS_SRC_ALPHA;

		case PLG_BLEND_DST_ALPHA:
			return GR_BLEND_DST_ALPHA;
		case PLG_BLEND_ONE_MINUS_DST_ALPHA:
			return GR_BLEND_ONE_MINUS_DST_ALPHA;

		case PLG_BLEND_DST_COLOR:
			return GR_BLEND_DST_COLOR;
		case PLG_BLEND_ONE_MINUS_DST_COLOR:
			return GR_BLEND_ONE_MINUS_DST_COLOR;

		case PLG_BLEND_SRC_ALPHA_SATURATE:
			return GR_BLEND_ALPHA_SATURATE;
	}
}

static void SetBlendMode( PLGBlend a, PLGBlend b ) {
	if ( a == PLG_BLEND_NONE || b == PLG_BLEND_NONE ) {
		grColorMask( FXTRUE, FXFALSE );
		return;
	}

	grColorMask( FXTRUE, FXTRUE );
	GrAlphaBlendFnc_t src = ConvertPlgBlendToGlideBlend( a );
	GrAlphaBlendFnc_t dst = ConvertPlgBlendToGlideBlend( b );
	grAlphaBlendFunction( src, dst, src, dst );
}

static void SetCullMode( PLGCullMode cullMode ) {
	GrCullMode_t cull;
	if ( cullMode == PLG_CULL_NEGATIVE ) {
		cull = GR_CULL_NEGATIVE;
	} else if ( cullMode == PLG_CULL_POSITIVE ) {
		cull = GR_CULL_POSITIVE;
	} else {
		cull = GR_CULL_DISABLE;
	}
	grCullMode( cull );
}

static void SetClearColour( PLColour colour ) {
	/* todo: convert our colour to whatever glide needs */
	//renderState.clearColour = colour;
}

static void ClearBuffers( unsigned int buffers ) {
	grBufferClear( renderState.clearColour, 0, 0 );
}

static void DrawPixel( int x, int y, PLColour colour ) {
	PLGVertex vertex;
	vertex.position.x = ( float ) x;
	vertex.position.y = ( float ) y;
	grDrawPoint( &vertex );
}

static void DrawMesh( PLGMesh *mesh, PLGShaderProgram *program ) {
}

const PLGDriverImportTable *DrvGlide_GetImportTable( void ) {
	static PLGDriverImportTable table;
	memset( &table, 0, sizeof( PLGDriverImportTable ) );

	table.Initialize = Initialize;
	table.Shutdown = Shutdown;

	table.SupportsHWShaders = SupportsHwShaders;
	table.GetMaxTextureUnits = GetMaxTextureUnits;
	table.GetMaxTextureSize = GetMaxTextureSize;
	table.SetClearColour = SetClearColour;
	table.ClearBuffers = ClearBuffers;

	table.DrawPixel = DrawPixel;

	return &table;
}
