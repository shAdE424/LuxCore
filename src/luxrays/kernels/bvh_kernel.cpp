#include <string>
namespace luxrays { namespace ocl {
std::string KernelSource_bvh = 
"#line 2 \"bvh_kernel.cl\"\n"
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
"#define BVHNodeData_IsLeaf(nodeData) ((nodeData) & 0x80000000u)\n"
"#define BVHNodeData_GetSkipIndex(nodeData) ((nodeData) & 0x7fffffffu)\n"
"#if (BVH_NODES_PAGE_COUNT > 1)\n"
"#define BVHNodeData_GetPageIndex(nodeData) (((nodeData) & 0x70000000u) >> 28)\n"
"#define BVHNodeData_GetNodeIndex(nodeData) ((nodeData) & 0x0fffffffu)\n"
"#endif\n"
"\n"
"#if (BVH_NODES_PAGE_COUNT > 1)\n"
"void NextNode(uint *pageIndex, uint *nodeIndex) {\n"
"	++(*nodeIndex);\n"
"	if (*nodeIndex >= BVH_NODES_PAGE_SIZE) {\n"
"		*nodeIndex = 0;\n"
"		++(*pageIndex);\n"
"	}\n"
"}\n"
"#endif\n"
"\n"
"#if (BVH_NODES_PAGE_COUNT == 8)\n"
"#define ACCELERATOR_INTERSECT_PARAM_DECL , __global const Point* restrict accelVertPage0, __global const Point* restrict accelVertPage1, __global const Point* restrict accelVertPage2, __global const Point* restrict accelVertPage3, __global const Point* restrict accelVertPage4, __global const Point* restrict accelVertPage5, __global const Point* restrict accelVertPage6, __global const Point* restrict accelVertPage7, __global const BVHArrayNode* restrict accelNodePage0, __global const BVHArrayNode* restrict accelNodePage1, __global const BVHArrayNode* restrict accelNodePage2, __global const BVHArrayNode* restrict accelNodePage3, __global const BVHArrayNode* restrict accelNodePage4, __global const BVHArrayNode* restrict accelNodePage5, __global const BVHArrayNode* restrict accelNodePage6, __global const BVHArrayNode* restrict accelNodePage7\n"
"#define ACCELERATOR_INTERSECT_PARAM , accelVertPage0, accelVertPage1, accelVertPage2, accelVertPage3, accelVertPage4, accelVertPage5, accelVertPage6, accelVertPage7, accelNodePage0, accelNodePage1, accelNodePage2, accelNodePage3, accelNodePage4, accelNodePage5, accelNodePage6, accelNodePage7\n"
"#elif (BVH_NODES_PAGE_COUNT == 7)\n"
"#define ACCELERATOR_INTERSECT_PARAM_DECL , __global const Point* restrict accelVertPage0, __global const Point* restrict accelVertPage1, __global const Point* restrict accelVertPage2, __global const Point* restrict accelVertPage3, __global const Point* restrict accelVertPage4, __global const Point* restrict accelVertPage5, __global const Point* restrict accelVertPage6, __global const BVHArrayNode* restrict accelNodePage0, __global const BVHArrayNode* restrict accelNodePage1, __global const BVHArrayNode* restrict accelNodePage2, __global const BVHArrayNode* restrict accelNodePage3, __global const BVHArrayNode* restrict accelNodePage4, __global const BVHArrayNode* restrict accelNodePage5, __global const BVHArrayNode* restrict accelNodePage6\n"
"#define ACCELERATOR_INTERSECT_PARAM , accelVertPage0, accelVertPage1, accelVertPage2, accelVertPage3, accelVertPage4, accelVertPage5, accelVertPage6, accelNodePage0, accelNodePage1, accelNodePage2, accelNodePage3, accelNodePage4, accelNodePage5, accelNodePage6\n"
"#elif (BVH_NODES_PAGE_COUNT == 6)\n"
"#define ACCELERATOR_INTERSECT_PARAM_DECL , __global const Point* restrict accelVertPage0, __global const Point* restrict accelVertPage1, __global const Point* restrict accelVertPage2, __global const Point* restrict accelVertPage3, __global const Point* restrict accelVertPage4, __global const Point* restrict accelVertPage5, __global const BVHArrayNode* restrict accelNodePage0, __global const BVHArrayNode* restrict accelNodePage1, __global const BVHArrayNode* restrict accelNodePage2, __global const BVHArrayNode* restrict accelNodePage3, __global const BVHArrayNode* restrict accelNodePage4, __global const BVHArrayNode* restrict accelNodePage5\n"
"#define ACCELERATOR_INTERSECT_PARAM , accelVertPage0, accelVertPage1, accelVertPage2, accelVertPage3, accelVertPage4, accelVertPage5, accelNodePage0, accelNodePage1, accelNodePage2, accelNodePage3, accelNodePage4, accelNodePage5\n"
"#elif (BVH_NODES_PAGE_COUNT == 5)\n"
"#define ACCELERATOR_INTERSECT_PARAM_DECL , __global const Point* restrict accelVertPage0, __global const Point* restrict accelVertPage1, __global const Point* restrict accelVertPage2, __global const Point* restrict accelVertPage3, __global const Point* restrict accelVertPage4, __global const BVHArrayNode* restrict accelNodePage0, __global const BVHArrayNode* restrict accelNodePage1, __global const BVHArrayNode* restrict accelNodePage2, __global const BVHArrayNode* restrict accelNodePage3, __global const BVHArrayNode* restrict accelNodePage4\n"
"#define ACCELERATOR_INTERSECT_PARAM , accelVertPage0, accelVertPage1, accelVertPage2, accelVertPage3, accelVertPage4, accelNodePage0, accelNodePage1, accelNodePage2, accelNodePage3, accelNodePage4\n"
"#elif (BVH_NODES_PAGE_COUNT == 4)\n"
"#define ACCELERATOR_INTERSECT_PARAM_DECL , __global const Point* restrict accelVertPage0, __global const Point* restrict accelVertPage1, __global const Point* restrict accelVertPage2, __global const Point* restrict accelVertPage3, __global const BVHArrayNode* restrict accelNodePage0, __global const BVHArrayNode* restrict accelNodePage1, __global const BVHArrayNode* restrict accelNodePage2, __global const BVHArrayNode* restrict accelNodePage3\n"
"#define ACCELERATOR_INTERSECT_PARAM , accelVertPage0, accelVertPage1, accelVertPage2, accelVertPage3, accelNodePage0, accelNodePage1, accelNodePage2, accelNodePage3\n"
"#elif (BVH_NODES_PAGE_COUNT == 3)\n"
"#define ACCELERATOR_INTERSECT_PARAM_DECL , __global const Point* restrict accelVertPage0, __global const Point* restrict accelVertPage1, __global const Point* restrict accelVertPage2, __global const BVHArrayNode* restrict accelNodePage0, __global const BVHArrayNode* restrict accelNodePage1, __global const BVHArrayNode* restrict accelNodePage2\n"
"#define ACCELERATOR_INTERSECT_PARAM , accelVertPage0, accelVertPage1, accelVertPage2, accelNodePage0, accelNodePage1, accelNodePage2\n"
"#elif (BVH_NODES_PAGE_COUNT == 2)\n"
"#define ACCELERATOR_INTERSECT_PARAM_DECL , __global const Point* restrict accelVertPage0, __global const Point* restrict accelVertPage1, __global const BVHArrayNode* restrict accelNodePage0, __global const BVHArrayNode* restrict accelNodePage1\n"
"#define ACCELERATOR_INTERSECT_PARAM , accelVertPage0, accelVertPage1, accelNodePage0, accelNodePage1\n"
"#elif (BVH_NODES_PAGE_COUNT == 1)\n"
"#define ACCELERATOR_INTERSECT_PARAM_DECL , __global const Point* restrict accelVertPage0, __global const BVHArrayNode* restrict accelNodePage0\n"
"#define ACCELERATOR_INTERSECT_PARAM , accelVertPage0, accelNodePage0\n"
"#elif (BVH_NODES_PAGE_COUNT == 0)\n"
"#define ACCELERATOR_INTERSECT_PARAM_DECL\n"
"#define ACCELERATOR_INTERSECT_PARAM\n"
"#elif\n"
"ERROR: unsuported BVH_NODES_PAGE_COUNT !!!\n"
"#endif\n"
"\n"
"void Accelerator_Intersect(\n"
"		const Ray *ray,\n"
"		RayHit *rayHit\n"
"		ACCELERATOR_INTERSECT_PARAM_DECL\n"
"		) {\n"
"#if (BVH_NODES_PAGE_COUNT == 0)\n"
"	rayHit->t = ray->maxt;\n"
"	rayHit->meshIndex = NULL_INDEX;\n"
"	rayHit->triangleIndex = NULL_INDEX;\n"
"	\n"
"	return;\n"
"#else\n"
"\n"
"	// Initialize vertex page references\n"
"#if (BVH_VERTS_PAGE_COUNT > 1)\n"
"	__global const Point* restrict accelVertPages[BVH_VERTS_PAGE_COUNT];\n"
"#if defined(BVH_VERTS_PAGE0)\n"
"	accelVertPages[0] = accelVertPage0;\n"
"#endif\n"
"#if defined(BVH_VERTS_PAGE1)\n"
"	accelVertPages[1] = accelVertPage1;\n"
"#endif\n"
"#if defined(BVH_VERTS_PAGE2)\n"
"	accelVertPages[2] = accelVertPage2;\n"
"#endif\n"
"#if defined(BVH_VERTS_PAGE3)\n"
"	accelVertPages[3] = accelVertPage3;\n"
"#endif\n"
"#if defined(BVH_VERTS_PAGE4)\n"
"	accelVertPages[4] = accelVertPage4;\n"
"#endif\n"
"#if defined(BVH_VERTS_PAGE5)\n"
"	accelVertPages[5] = accelVertPage5;\n"
"#endif\n"
"#if defined(BVH_VERTS_PAGE6)\n"
"	accelVertPages[6] = accelVertPage6;\n"
"#endif\n"
"#if defined(BVH_VERTS_PAGE7)\n"
"	accelVertPages[7] = accelVertPage7;\n"
"#endif\n"
"#endif\n"
"\n"
"	// Initialize node page references\n"
"#if (BVH_NODES_PAGE_COUNT > 1)\n"
"	__global const BVHArrayNode* restrict accelNodePages[BVH_NODES_PAGE_COUNT];\n"
"#if defined(BVH_NODES_PAGE0)\n"
"	accelNodePages[0] = accelNodePage0;\n"
"#endif\n"
"#if defined(BVH_NODES_PAGE1)\n"
"	accelNodePages[1] = accelNodePage1;\n"
"#endif\n"
"#if defined(BVH_NODES_PAGE2)\n"
"	accelNodePages[2] = accelNodePage2;\n"
"#endif\n"
"#if defined(BVH_NODES_PAGE3)\n"
"	accelNodePages[3] = accelNodePage3;\n"
"#endif\n"
"#if defined(BVH_NODES_PAGE4)\n"
"	accelNodePages[4] = accelNodePage4;\n"
"#endif\n"
"#if defined(BVH_NODES_PAGE5)\n"
"	accelNodePages[5] = accelNodePage5;\n"
"#endif\n"
"#if defined(BVH_NODES_PAGE6)\n"
"	accelNodePages[6] = accelNodePage6;\n"
"#endif\n"
"#if defined(BVH_NODES_PAGE7)\n"
"	accelNodePages[7] = accelNodePage7;\n"
"#endif\n"
"\n"
"	const uint rootNodeData = accelNodePage0[0].nodeData;\n"
"	const uint stopPage = BVHNodeData_GetPageIndex(rootNodeData);\n"
"	const uint stopNode = BVHNodeData_GetNodeIndex(rootNodeData); // Non-existent\n"
"	uint currentPage = 0; // Root Node Page\n"
"#else\n"
"	const uint stopNode = BVHNodeData_GetSkipIndex(accelNodePage0[0].nodeData); // Non-existent\n"
"#endif\n"
"\n"
"	const float3 rayOrig = (float3)(ray->o.x, ray->o.y, ray->o.z);\n"
"	const float3 rayDir = (float3)(ray->d.x, ray->d.y, ray->d.z);\n"
"	const float mint = ray->mint;\n"
"	float maxt = ray->maxt;\n"
"\n"
"	const float3 invRayDir = 1.f / rayDir;\n"
"\n"
"	uint hitMeshIndex = NULL_INDEX;\n"
"	uint hitTriangleIndex = NULL_INDEX;\n"
"	uint currentNode = 0; // Root Node\n"
"\n"
"	float b1, b2;\n"
"#if (BVH_NODES_PAGE_COUNT == 1)\n"
"	while (currentNode < stopNode) {\n"
"		__global const BVHArrayNode* restrict node = &accelNodePage0[currentNode];\n"
"#else\n"
"	while ((currentPage < stopPage) || (currentNode < stopNode)) {\n"
"		__global const BVHArrayNode* restrict accelNodePage = accelNodePages[currentPage];\n"
"		__global const BVHArrayNode* restrict node = &accelNodePage[currentNode];\n"
"#endif\n"
"		// Read the node\n"
"		__global float4* restrict data = (__global float4* restrict)node;\n"
"		const float4 data0 = *data++;\n"
"		const float4 data1 = *data;\n"
"\n"
"		//const uint nodeData = node->nodeData;\n"
"		const uint nodeData = as_uint(data1.s2);\n"
"		if (BVHNodeData_IsLeaf(nodeData)) {\n"
"			// It is a leaf, check the triangle\n"
"\n"
"			//const uint i0 = node->triangleLeaf.v[0];\n"
"			//const uint i1 = node->triangleLeaf.v[1];\n"
"			//const uint i2 = node->triangleLeaf.v[2];\n"
"			const uint v0 = as_uint(data0.s0);\n"
"			const uint v1 = as_uint(data0.s1);\n"
"			const uint v2 = as_uint(data0.s2);\n"
"\n"
"#if (BVH_VERTS_PAGE_COUNT == 1)\n"
"			// Fast path for when there is only one memory page\n"
"			const float3 p0 = VLOAD3F(&accelVertPage0[v0].x);\n"
"			const float3 p1 = VLOAD3F(&accelVertPage0[v1].x);\n"
"			const float3 p2 = VLOAD3F(&accelVertPage0[v2].x);\n"
"#else\n"
"			const uint pv0 = (v0 & 0xe0000000u) >> 29;\n"
"			const uint iv0 = (v0 & 0x1fffffffu);\n"
"			__global Point* restrict vp0 = accelVertPages[pv0];\n"
"			const float3 p0 = VLOAD3F(&vp0[iv0].x);\n"
"\n"
"			const uint pv1 = (v1 & 0xe0000000u) >> 29;\n"
"			const uint iv1 = (v1 & 0x1fffffffu);\n"
"			__global Point* restrict vp1 = accelVertPages[pv1];\n"
"			const float3 p1 = VLOAD3F(&vp1[iv1].x);\n"
"\n"
"			const uint pv2 = (v2 & 0xe0000000u) >> 29;\n"
"			const uint iv2 = (v2 & 0x1fffffffu);\n"
"			__global Point* restrict vp2 = accelVertPages[pv2];\n"
"			const float3 p2 = VLOAD3F(&vp2[iv2].x);\n"
"#endif\n"
"\n"
"			//const uint triangleIndex = node->triangleLeaf.triangleIndex;\n"
"			const uint meshIndex = as_uint(data0.s3);\n"
"			const uint triangleIndex = as_uint(data1.s0);\n"
"\n"
"			Triangle_Intersect(rayOrig, rayDir, mint, &maxt, &hitMeshIndex, &hitTriangleIndex,\n"
"					&b1, &b2, meshIndex, triangleIndex, p0, p1, p2);\n"
"#if (BVH_NODES_PAGE_COUNT == 1)\n"
"			++currentNode;\n"
"#else\n"
"			NextNode(&currentPage, &currentNode);\n"
"#endif\n"
"		} else {\n"
"			// It is a node, check the bounding box\n"
"			//const float3 pMin = VLOAD3F(&node->bvhNode.bboxMin[0]);\n"
"			//const float3 pMax = VLOAD3F(&node->bvhNode.bboxMax[0]);\n"
"			const float3 pMin = (float3)(data0.s0, data0.s1, data0.s2);\n"
"			const float3 pMax = (float3)(data0.s3, data1.s0, data1.s1);\n"
"\n"
"			if (BBox_IntersectP(pMin, pMax, rayOrig, invRayDir, mint, maxt)) {\n"
"#if (BVH_NODES_PAGE_COUNT == 1)\n"
"				++currentNode;\n"
"#else\n"
"				NextNode(&currentPage, &currentNode);\n"
"#endif\n"
"			} else {\n"
"#if (BVH_NODES_PAGE_COUNT == 1)\n"
"				// I don't need to use BVHNodeData_GetSkipIndex() here because\n"
"				// I already know the flag (i.e. the last bit) is 0\n"
"				currentNode = nodeData;\n"
"#else\n"
"				currentPage = BVHNodeData_GetPageIndex(nodeData);\n"
"				currentNode = BVHNodeData_GetNodeIndex(nodeData);\n"
"#endif\n"
"			}\n"
"		}\n"
"	}\n"
"\n"
"	rayHit->t = maxt;\n"
"	rayHit->b1 = b1;\n"
"	rayHit->b2 = b2;\n"
"	rayHit->meshIndex = hitMeshIndex;\n"
"	rayHit->triangleIndex = hitTriangleIndex;\n"
"\n"
"#endif\n"
"}\n"
"\n"
"__kernel __attribute__((work_group_size_hint(64, 1, 1))) void Accelerator_Intersect_RayBuffer(\n"
"		__global const Ray* restrict rays,\n"
"		__global RayHit *rayHits,\n"
"		const uint rayCount\n"
"		ACCELERATOR_INTERSECT_PARAM_DECL\n"
"		) {\n"
"	// Select the ray to check\n"
"	const int gid = get_global_id(0);\n"
"	if (gid >= rayCount)\n"
"		return;\n"
"\n"
"	Ray ray;\n"
"	Ray_ReadAligned4_Private(&rays[gid], &ray);\n"
"\n"
"	RayHit rayHit;\n"
"	Accelerator_Intersect(\n"
"		&ray,\n"
"		&rayHit\n"
"		ACCELERATOR_INTERSECT_PARAM\n"
"		);\n"
"\n"
"	// Write result\n"
"	__global RayHit *memRayHit = &rayHits[gid];\n"
"	memRayHit->t = rayHit.t;\n"
"	memRayHit->b1 = rayHit.b1;\n"
"	memRayHit->b2 = rayHit.b2;\n"
"	memRayHit->meshIndex = rayHit.meshIndex;\n"
"	memRayHit->triangleIndex = rayHit.triangleIndex;\n"
"}\n"
; } }
