/**
 * Hei Platform Library
 * Copyright (C) 2017-2021 Mark E Sowden <hogsy@oldtimes-software.com>
 * This software is licensed under MIT. See LICENSE for more details.
 */

#include "plugin.h"

#include <plgraphics/plg.h>
#include <plgraphics/plg_camera.h>

#include <plcore/pl_parse.h>

PLGDriverImportTable graphicsInterface = {
		.Initialize = GLInitialize,
		.Shutdown = GLShutdown,

		.InsertDebugMarker = GLInsertDebugMarker,
		.PushDebugGroupMarker = GLPushDebugGroupMarker,
		.PopDebugGroupMarker = GLPopDebugGroupMarker,

		.SupportsHWShaders = GLSupportsHWShaders,
		.GetMaxTextureUnits = GLGetMaxTextureUnits,
		.GetMaxTextureSize = GLGetMaxTextureSize,

		.EnableState = GLEnableState,
		.DisableState = GLDisableState,

		.SetBlendMode = GLSetBlendMode,
		.SetCullMode = GLSetCullMode,

		.SetClearColour = GLSetClearColour,
		.ClearBuffers = GLClearBuffers,

		//.DrawPixel = ,

		.SetDepthBufferMode = GLSetDepthBufferMode,
		.SetDepthMask = GLSetDepthMask,

		.CreateMesh = GLCreateMesh,
		.UploadMesh = GLUploadMesh,
		.DrawMesh = GLDrawMesh,
		.DrawInstancedMesh = GLDrawInstancedMesh,
		.DeleteMesh = GLDeleteMesh,

		.CreateFrameBuffer = GLCreateFrameBuffer,
		.DeleteFrameBuffer = GLDeleteFrameBuffer,
		.BindFrameBuffer = GLBindFrameBuffer,
		.GetFrameBufferTextureAttachment = GLGetFrameBufferTextureAttachment,
		.BlitFrameBuffers = GLBlitFrameBuffers,

		.CreateTexture = GLCreateTexture,
		.DeleteTexture = GLDeleteTexture,
		.BindTexture = GLBindTexture,
		.UploadTexture = GLUploadTexture,
		.SwizzleTexture = GLSwizzleTexture,
		.SetTextureAnisotropy = GLSetTextureAnisotropy,
		.ActiveTexture = GLActiveTexture,

		.CreateCamera = GLCreateCamera,
		.DestroyCamera = GLDestroyCamera,
		.SetupCamera = GLSetupCamera,

		.CreateShaderProgram = GLCreateShaderProgram,
		.DestroyShaderProgram = GLDestroyShaderProgram,
		.AttachShaderStage = GLAttachShaderStage,
		//.DetachShaderStage = ,
		.LinkShaderProgram = GLLinkShaderProgram,
		.SetShaderProgram = GLSetShaderProgram,
		.CreateShaderStage = GLCreateShaderStage,
		.DestroyShaderStage = GLDestroyShaderStage,
		.CompileShaderStage = GLCompileShaderStage,
		.SetShaderUniformValue = GLSetShaderUniformValue,

		//.StencilFunction = ,
};
