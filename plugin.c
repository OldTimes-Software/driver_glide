/**
 * Hei Platform Library
 * Copyright (C) 2017-2021 Mark E Sowden <hogsy@oldtimes-software.com>
 * This software is licensed under MIT. See LICENSE for more details.
 */

#include "plugin.h"

static PLGDriverDescription pluginDesc = {
        .identifier = "glide",
        .description = "3dfx Glide Graphics Driver.",
        .driverVersion = { 0, 0, 1 },
        .coreInterfaceVersion = { PL_PLUGIN_INTERFACE_VERSION_MAJOR, PL_PLUGIN_INTERFACE_VERSION_MINOR },
        .graphicsInterfaceVersion = { PLG_INTERFACE_VERSION_MAJOR, PLG_INTERFACE_VERSION_MINOR },
};

const PLGDriverExportTable *gInterface = NULL;

PL_EXPORT const PLGDriverDescription *QueryGraphicsDriver( void ) {
	return &pluginDesc;
}

int glLogLevel;

PL_EXPORT const PLGDriverImportTable *InitializeGraphicsDriver( const PLGDriverExportTable *functionTable ) {
	gInterface = functionTable;

	glLogLevel = gInterface->core->AddLogLevel( "plugin/glide", PLColourRGB( 255, 255, 255 ), true );

	const PLGDriverImportTable *DrvGlide_GetImportTable( void );
	return DrvGlide_GetImportTable();
}
