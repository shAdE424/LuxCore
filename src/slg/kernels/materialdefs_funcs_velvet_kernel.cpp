#include <string>
namespace slg { namespace ocl {
std::string KernelSource_materialdefs_funcs_velvet = 
"#line 2 \"materialdefs_funcs_velvet.cl\"\n"
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
"// Velvet material\n"
"//------------------------------------------------------------------------------\n"
"\n"
"#if defined (PARAM_ENABLE_MAT_VELVET)\n"
"\n"
"BSDFEvent VelvetMaterial_GetEventTypes() {\n"
"	return DIFFUSE | REFLECT;\n"
"}\n"
"\n"
"float3 VelvetMaterial_Evaluate(\n"
"		__global HitPoint *hitPoint, const float3 lightDir, const float3 eyeDir,\n"
"		BSDFEvent *event, float *directPdfW,\n"
"		const float3 kdVal,\n"
"		const float A1, const float A2, const float A3,\n"
"		const float delta) {\n"
"	if (directPdfW)\n"
"		*directPdfW = fabs(lightDir.z * M_1_PI_F);\n"
"\n"
"	*event = DIFFUSE | REFLECT;\n"
"\n"
"	const float3 kd = Spectrum_Clamp(kdVal);\n"
"	const float cosv = -dot(lightDir, eyeDir);\n"
"\n"
"	// Compute phase function\n"
"\n"
"	const float B = 3.0f * cosv;\n"
"\n"
"	float p = 1.0f + A1 * cosv + A2 * 0.5f * (B * cosv - 1.0f) + A3 * 0.5 * (5.0f * cosv * cosv * cosv - B);\n"
"	p = p / (4.0f * M_PI_F);\n"
" \n"
"	p = (p * delta) / fabs(eyeDir.z);\n"
"\n"
"	// Clamp the BRDF (page 7)\n"
"	if (p > 1.0f)\n"
"		p = 1.0f;\n"
"	else if (p < 0.0f)\n"
"		p = 0.0f;\n"
"\n"
"	return p * kd;\n"
"}\n"
"\n"
"float3 VelvetMaterial_Sample(\n"
"		__global HitPoint *hitPoint, const float3 fixedDir, float3 *sampledDir,\n"
"		const float u0, const float u1,\n"
"#if defined(PARAM_HAS_PASSTHROUGH)\n"
"		const float passThroughEvent,\n"
"#endif\n"
"		float *pdfW, float *cosSampledDir, BSDFEvent *event,\n"
"		const BSDFEvent requestedEvent,\n"
"		const float3 kdVal,\n"
"		const float A1, const float A2, const float A3,\n"
"		const float delta) {\n"
"	if (!(requestedEvent & (DIFFUSE | REFLECT)) ||\n"
"			(fabs(fixedDir.z) < DEFAULT_COS_EPSILON_STATIC))\n"
"		return BLACK;\n"
"\n"
"	*sampledDir = (signbit(fixedDir.z) ? -1.f : 1.f) * CosineSampleHemisphereWithPdf(u0, u1, pdfW);\n"
"\n"
"	*cosSampledDir = fabs((*sampledDir).z);\n"
"	if (*cosSampledDir < DEFAULT_COS_EPSILON_STATIC)\n"
"		return BLACK;\n"
"\n"
"	*event = DIFFUSE | REFLECT;\n"
"\n"
"	const float3 kd = Spectrum_Clamp(kdVal);\n"
"	const float cosv = dot(-fixedDir, *sampledDir);;\n"
"\n"
"	// Compute phase function\n"
"\n"
"	const float B = 3.0f * cosv;\n"
"\n"
"	float p = 1.0f + A1 * cosv + A2 * 0.5f * (B * cosv - 1.0f) + A3 * 0.5 * (5.0f * cosv * cosv * cosv - B);\n"
"	p = p / (4.0f * M_PI_F);\n"
" \n"
"	p = (p * delta) / fabs(fixedDir.z);\n"
"\n"
"	// Clamp the BRDF (page 7)\n"
"	if (p > 1.0f)\n"
"		p = 1.0f;\n"
"	else if (p < 0.0f)\n"
"		p = 0.0f;\n"
"\n"
"	return kd * (p / *pdfW);\n"
"}\n"
"\n"
"#endif\n"
; } }
