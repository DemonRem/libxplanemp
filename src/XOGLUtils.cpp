/*
 * Copyright (c) 2005, Ben Supnik and Chris Serio.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include "XOGLUtils.h"

// This had to be renamed because on Linux, namespaces appear to be shared between ourselves and XPlane
// so i would end up overwritting XPlanes function pointer!

#if IBM
PFNGLBINDBUFFERARBPROC			glBindBufferARB			 = NULL;
PFNGLACTIVETEXTUREARBPROC		glActiveTextureARB		 = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB = NULL;
PFNGLMULTITEXCOORD2FARBPROC		glMultiTexCoord2fARB	 = NULL;
PFNGLMULTITEXCOORD2FVARBPROC	glMultiTexCoord2fvARB	 = NULL;
PFNGLGENERATEMIPMAPPROC			glGenerateMipmap		 = NULL;
#endif

#if LIN

#define		wglGetProcAddress(x)		glXGetProcAddressARB((GLubyte*) (x))

#endif

/**************************************************
			   Utilities Initialization
***************************************************/

bool	OGL_UtilsInit()
{
	static bool firstTime = true;
	if(firstTime)
	{
		// Initialize all OGL Function Pointers
#if IBM		
		glBindBufferARB			 = (PFNGLBINDBUFFERARBPROC)			 wglGetProcAddress("glBindBufferARB"		);
		glActiveTextureARB 		 = (PFNGLACTIVETEXTUREARBPROC)		 wglGetProcAddress("glActiveTextureARB"		 );
		glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC) wglGetProcAddress("glClientActiveTextureARB");
		glMultiTexCoord2fARB	 = (PFNGLMULTITEXCOORD2FARBPROC )	 wglGetProcAddress("glMultiTexCoord2fARB"    );
		glMultiTexCoord2fvARB	 = (PFNGLMULTITEXCOORD2FVARBPROC )	 wglGetProcAddress("glMultiTexCoord2fvARB"   );
		glGenerateMipmap		 = (PFNGLGENERATEMIPMAPPROC)		 wglGetProcAddress("glGenerateMipmap"		 );
#endif		
		firstTime = false;
	}

#if IBM
	// Make sure everything got initialized
	if(glBindBufferARB &&
			glActiveTextureARB &&
			glClientActiveTextureARB &&
			glMultiTexCoord2fARB &&
			glMultiTexCoord2fvARB &&
			glGenerateMipmap)
	{
		return true;
	}
	else
		return false;
#else
	return true;
#endif

}
