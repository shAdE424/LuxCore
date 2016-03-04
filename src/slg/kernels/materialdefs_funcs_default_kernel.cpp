#include <string>
namespace slg { namespace ocl {
std::string KernelSource_materialdefs_funcs_default = 
"#line 2 \"material_funcs_default.cl\"\n"
"\n"
"/***************************************************************************\n"
" * Copyright 1998-2015 by authors (see AUTHORS.txt)                        *\n"
" *                                                                         *\n"
" *   This file is part of LuxRender.                                       *\n"
" *                                                                         *\n"
" * Licensed under the Apache License, Version 2.0 (the \"License\");         *\n"
" * you may not use this file except in compliance with the License.        *\n"
" * You may obtain a copy of the License at                                 *\n"
" *                                                                         *\n"
" *     http://www.apache.org/licenses/LICENSE-2.0                          *\n"
" *                                                                         *\n"
" * Unless required by applicable law or agreed to in writing, software     *\n"
" * distributed under the License is distributed on an \"AS IS\" BASIS,       *\n"
" * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*\n"
" * See the License for the specific language governing permissions and     *\n"
" * limitations under the License.                                          *\n"
" ***************************************************************************/\n"
"\n"
"//------------------------------------------------------------------------------\n"
"// Default material functions\n"
"//------------------------------------------------------------------------------\n"
"\n"
"//------------------------------------------------------------------------------\n"
"// DefaultMatteMaterial_IsDelta\n"
"//------------------------------------------------------------------------------\n"
"\n"
"bool DefaultMaterial_IsDelta() {\n"
"	return false;\n"
"}\n"
"\n"
"//------------------------------------------------------------------------------\n"
"// DefaultMaterial_GetPassThroughTransparency\n"
"//------------------------------------------------------------------------------\n"
"\n"
"#if defined(PARAM_HAS_PASSTHROUGH)\n"
"float3 DefaultMaterial_GetPassThroughTransparency(__global const Material *material,\n"
"		__global HitPoint *hitPoint, const float3 localFixedDir, const float passThroughEvent\n"
"		TEXTURES_PARAM_DECL) {\n"
"	const uint transpTexIndex = material->transpTexIndex;\n"
"\n"
"	if (transpTexIndex != NULL_INDEX) {\n"
"		const float weight = clamp(\n"
"				Texture_GetFloatValue(transpTexIndex, hitPoint\n"
"					TEXTURES_PARAM),\n"
"				0.f, 1.f);\n"
"\n"
"		return (passThroughEvent > weight) ? WHITE : BLACK;\n"
"	} else\n"
"		return BLACK;\n"
"}\n"
"#endif\n"
"\n"
"//------------------------------------------------------------------------------\n"
"// DefaultMaterial_GetEmittedRadiance\n"
"//------------------------------------------------------------------------------\n"
"\n"
"float3 DefaultMaterial_GetEmittedRadiance(__global const Material *material, __global HitPoint *hitPoint\n"
"		TEXTURES_PARAM_DECL) {\n"
"	const uint emitTexIndex = material->emitTexIndex;\n"
"	if (emitTexIndex == NULL_INDEX)\n"
"		return BLACK;\n"
"\n"
"	return\n"
"#if defined(PARAM_TRIANGLE_LIGHT_HAS_VERTEX_COLOR)\n"
"		VLOAD3F(hitPoint->color.c) *\n"
"#endif\n"
"		Texture_GetSpectrumValue(emitTexIndex, hitPoint\n"
"				TEXTURES_PARAM);\n"
"}\n"
"\n"
"//------------------------------------------------------------------------------\n"
"// DefaultMaterial_GetInteriorVolume\n"
"//------------------------------------------------------------------------------\n"
"\n"
"#if defined(PARAM_HAS_VOLUMES)\n"
"uint DefaultMaterial_GetInteriorVolume(__global const Material *material) {\n"
"	return material->interiorVolumeIndex;\n"
"}\n"
"#endif\n"
"\n"
"//------------------------------------------------------------------------------\n"
"// DefaultMaterial_GetExteriorVolume\n"
"//------------------------------------------------------------------------------\n"
"\n"
"#if defined(PARAM_HAS_VOLUMES)\n"
"uint DefaultMaterial_GetExteriorVolume(__global const Material *material) {\n"
"	return material->exteriorVolumeIndex;\n"
"}\n"
"#endif\n"
; } }
