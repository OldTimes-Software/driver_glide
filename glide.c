/*
MIT License

Copyright (c) 2017-2021 Mark E Sowden <hogsy@oldtimes-software.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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
