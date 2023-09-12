#include "Renderer.h"
#include "../nclgl/HeightMap.h"
#include "../nclgl/HeightMapSceneNode.h"
#include "../nclgl/SatelliteSceneNode.h"
#include "../nclgl/WaterSceneNode.h"
#include "../nclgl/MeshMaterial.h"
#include "../nclgl/MeshAnimation.h"
#include<algorithm>

Renderer::Renderer(Window& parent) : OGLRenderer(parent) {

	heightMap[0] = new HeightMap(TEXTUREDIR"towers.png");

	heightMap[1] = new HeightMap(TEXTUREDIR"heightmap_new.png");

	camera = new Camera(-40, 270, Vector3());

	Vector3 dimensions = heightMap[0]->GetHeightmapSize();
	camera->SetPosition(dimensions * Vector3(0.5, 7, 0.56));
	camera->ToggleMoveCamera();
	movement = 0;

	root = new SceneNode();
	
	cube = Mesh::LoadFromMeshFile("OffsetCubeY.msh");
	quad = Mesh::GenerateQuad();

	/*textures[1] = SOIL_load_OGL_texture(TEXTUREDIR"paint1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
	textures[0] = SOIL_load_OGL_texture(TEXTUREDIR"stainedglass.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);*/

	//Maps for the scene

	shader[0] = new Shader("TexturedVertex-Course.glsl", "TerrainFragment.glsl");
	shader[1] = new Shader("TexturedVertex-Course.glsl", "Terrain2Fragment.glsl");


	terrainTex[0] = SOIL_load_OGL_texture(TEXTUREDIR"desert_sand2_d.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures_1[0] = SOIL_load_OGL_texture(TEXTUREDIR"desert_wet_d.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures_1[1] = SOIL_load_OGL_texture(TEXTUREDIR"water.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures_1[2] = SOIL_load_OGL_texture(TEXTUREDIR"grass_autumn_orn_d.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	terrainNor[0] = SOIL_load_OGL_texture(TEXTUREDIR"desert_sand2_n.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	normals_1[0] = SOIL_load_OGL_texture(TEXTUREDIR"desert_wet_n.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	normals_1[1] = SOIL_load_OGL_texture(TEXTUREDIR"waterbump.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	normals_1[2] = SOIL_load_OGL_texture(TEXTUREDIR"grass_autumn_n.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	terrainSpec[0] = SOIL_load_OGL_texture(TEXTUREDIR"desert_sand2_s.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	spec_1[0] = SOIL_load_OGL_texture(TEXTUREDIR"desert_wet_n.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	spec_1[1] = normals_1[1];
	spec_1[2] = SOIL_load_OGL_texture(TEXTUREDIR"grass_autumn_s.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	
	splatmap[0] = SOIL_load_OGL_texture(TEXTUREDIR"towers_specmap2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);


	terrainTex[1] = SOIL_load_OGL_texture(TEXTUREDIR"Barren Reds.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures_2[0] = SOIL_load_OGL_texture(TEXTUREDIR"desert_wet_d.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures_2[1] = SOIL_load_OGL_texture(TEXTUREDIR"water.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures_2[2] = SOIL_load_OGL_texture(TEXTUREDIR"grass_autumn_red_d.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	terrainNor[1] = SOIL_load_OGL_texture(TEXTUREDIR"Barren RedsDOT3.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	normals_2[0] = SOIL_load_OGL_texture(TEXTUREDIR"desert_wet_n.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	normals_2[1] = SOIL_load_OGL_texture(TEXTUREDIR"waterbump.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	normals_2[2] = SOIL_load_OGL_texture(TEXTUREDIR"grass_autumn_n.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	terrainSpec[1] = SOIL_load_OGL_texture(TEXTUREDIR"Barren RedsSPE4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	spec_2[0] = SOIL_load_OGL_texture(TEXTUREDIR"desert_wet_n.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	spec_2[1] = normals_1[1];
	spec_2[2] = SOIL_load_OGL_texture(TEXTUREDIR"grass_autumn_s.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	splatmap[1] = SOIL_load_OGL_texture(TEXTUREDIR"splatmap_new.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	if (!terrainTex[0] || !shader[0]->LoadSuccess() || !textures_1[0] || !textures_1[2] || !textures_1[1] || !splatmap[0]) {
		return;
	}

	if (!terrainNor[0]|| !normals_1[0] || !normals_1[2] || !normals_1[1]) {
		return;
	}

	if (!terrainSpec[0] || !spec_1[0] || !spec_1[2] || !spec_1[1]) {
		return;
	}

	if (!terrainTex[1] || !shader[1]->LoadSuccess() || !textures_2[0] || !textures_2[2] || !textures_2[1] || !splatmap[1]) {
		return;
	}

	if (!terrainNor[1] || !normals_2[0] || !normals_2[2] || !normals_2[1]) {
		return;
	}

	if (!terrainSpec[1] || !spec_2[0] || !spec_2[2] || !spec_2[1]) {
		return;
	}

	HeightMapSceneNode* baseMap = new HeightMapSceneNode(heightMap[0],shader[0], terrainTex[0]);
	
	for (int i = 0; i < 3; i++) {
		baseMap->SetSubTex(i, textures_1[i]);
		baseMap->SetSubNor(i, normals_1[i]);
		baseMap->SetSubSpec(i, spec_1[i]);
	}
	baseMap->SetNormalMap(terrainNor[0]);
	baseMap->SetSpecMap(terrainSpec[0]);
	baseMap->SetSplatMap(splatmap[0]);

	std::cout << "baseMap id:" << baseMap->GetValue()<<"\n";

	SatelliteSceneNode* secondMap = new SatelliteSceneNode(heightMap[1], shader[1], terrainTex[1], 50, 1, Y_AXIS, dimensions);
	
	HeightMapSceneNode* child =(HeightMapSceneNode*) *(secondMap->GetChildIteratorStart());

	for (int i = 0; i < 3; i++) {
		child->SetSubTex(i, textures_2[i]);
		child->SetSubNor(i, normals_2[i]);
		child->SetSubSpec(i, spec_2[i]);
	}
	child->SetNormalMap(terrainNor[1]);
	child->SetSpecMap(terrainSpec[1]);
	child->SetSplatMap(splatmap[1]);

	std::cout << "subMap id:" << secondMap->GetValue() << "\n";
	//secondMap->SetTransform(Matrix4::Translation(heightMap[1]->GetHeightmapSize()*Vector3(2, 0,1 )));

	baseMap->AddChild(secondMap);
	
	root->AddChild(baseMap);



	for (int i = 0; i < 2; i++)
	{
		SetTextureRepeating(terrainTex[i], true);
		SetTextureRepeating(terrainNor[i], true);
		SetTextureRepeating(terrainSpec[i], true);
	}
	
	for (int i = 0; i < 3; i++) {
		SetTextureRepeating(textures_1[i], true);
		SetTextureRepeating(normals_1[i], true);
		SetTextureRepeating(spec_1[i], true);

		SetTextureRepeating(textures_2[i], true);
		SetTextureRepeating(normals_2[i], true);
		SetTextureRepeating(spec_2[i], true);
	}

	// Adding Skeleton 

	shader[2] = new Shader("SkinningVertex-Course.glsl", "TexturedFragment-Course.glsl");

	if (!shader[2]->LoadSuccess()) {
		return;
	}

	meshes[0] = Mesh::LoadFromMeshFile("Role_T.msh");
	anim = new MeshAnimation("Role_T.anm");
	material = new MeshMaterial("Role_T.mat");

	for (int i = 0; i < meshes[0]->GetSubMeshCount(); i++) {
		const MeshMaterialEntry* matEntry = material->GetMaterialForLayer(i);
		const string* filename = nullptr;
		matEntry->GetEntry("Diffuse", &filename);
		string path = TEXTUREDIR + (*filename);
		GLuint texId = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		matTextures.emplace_back(texId);
	}

	SceneNode* Character = new SceneNode(meshes[0], Vector4(1, 1, 1, 1), shader[2]);

	Character->SetTransform(Matrix4::Translation(Vector3(heightMap[0]->GetHeightmapSize().x*0.5, dimensions.y*0.5, heightMap[0]->GetHeightmapSize().x * 0.5)));
	Character->SetModelScale(Vector3(100, 100, 100));

	baseMap->AddChild(Character);

	currentFrame = 0;
	frameTime = 0.0f;

	//Cube Robot
	shader[3] = new Shader("SceneVertex.glsl", "SceneFragment.glsl");
	shader[4] = new Shader("FireflyVertex.glsl", "FireflyFragment.glsl");

	if (!shader[3]->LoadSuccess() || !shader[4]->LoadSuccess()) {
		return;
	}
	CubeRobot* robot = new CubeRobot(cube, shader[3]);
	robot->SetTransform(Matrix4::Translation(Vector3(dimensions.x*0.5, 0, dimensions.z*0.5)));
	robot->SetModelScale(Vector3(15, 15, 15));
	
	child->AddChild(robot);

	// Point lights as fireflies with mesh

	sphere = Mesh::LoadFromMeshFile("Sphere.msh");

	for (int i = 0; i < 25; i++) {
		Vector3 position = Vector3(dimensions.x * 0.5 + rand() % 100 * 2 - 100, dimensions.y*0.5 + rand() % 100 * 2 - 100, dimensions.z * 0.5 + rand() % 250 * 2 - 250);
		fireflies[i] = new Firefly(sphere,position, Vector4(0.5f + (float)(rand() / (float)RAND_MAX), 0.5f + (float)(rand() / (float)RAND_MAX), 0.5f + (float)(rand() / (float)RAND_MAX), 1),5);
		fireflies[i]->SetModelScale(Vector3(20, 20, 20));
		baseMap->AddChild(fireflies[i]);
		fireflies[i]->SetShader(shader[4]);
	}

	for (int i = 25; i < 50; i++) {
		Vector3 childMapSize = heightMap[1]->GetHeightmapSize();
		Vector3 position = Vector3(childMapSize.x * 0.5+ rand() %100*2 -100, childMapSize.y * 0.5, childMapSize.z * 0.5 + rand() % 100 * 2 - 100);
		fireflies[i] = new Firefly(sphere, position, Vector4(0.5f + (float)(rand() / (float)RAND_MAX), 0.5f + (float)(rand() / (float)RAND_MAX), 0.5f + (float)(rand() / (float)RAND_MAX), 1), 5);
		fireflies[i]->SetModelScale(Vector3(20, 20, 20));
		child->AddChild(fireflies[i]);
		fireflies[i]->SetShader(shader[4]);

	}

	// CubeMap

	cubeMap = SOIL_load_OGL_cubemap(TEXTUREDIR"rusted_west.jpg", TEXTUREDIR"rusted_east.jpg", TEXTUREDIR"rusted_up.jpg", TEXTUREDIR"rusted_down.jpg", TEXTUREDIR"rusted_south.jpg", TEXTUREDIR"rusted_north.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);

	shader[5] = new Shader("skyboxVertex.glsl", "skyboxFragment.glsl");
	if (!shader[5]->LoadSuccess()) {
		return;
	}

	//water and reflection

	shader[6] = new Shader("reflectVertex-Course.glsl", "reflectFragment-Course.glsl");
	if (!shader[6]->LoadSuccess()) {
		return;
	}

	WaterSceneNode* water = new WaterSceneNode(quad, Vector4(1, 1, 1, 1), shader[6], textures_1[1], cubeMap, heightMap[1]->GetHeightmapSize());
	child->AddChild(water);

	/*SetTextureRepeating(terrainNor[0], true);
	for (int i = 0; i < 3; i++) {
		SetTextureRepeating(normals_1[i], true);
	}*/
	SwitchToPerspective();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	/*usingDepth = false;
	filtering = true;
	repeating = false;

	blendMode = 0;
	depthMode = -1;
	modifyObject = true;*/

	init = true;

}


Renderer::~Renderer(void) {
	delete heightMap[0];
	delete heightMap[1];
	delete camera;
	for (int i = 0; i < 6; i++) {
		delete shader[i];
	}
	delete cube;
	delete quad;
	delete anim;
	delete material;

	for (int i = 0; i < 50; i++) {
		delete fireflies[i];
	}
}

void Renderer::updateCamera(float time, float dt) {
	
	switch (movement) {
	case 0:
		camera->SetPitch(-70);
		camera->SetSpeed(200);
		if (camera->GetPosition().y > 300) {
			camera->moveForward(dt);
		}
		else { movement = 1; startTime = time; endTime = time + 10; camera->SetYaw(90); }
		break;
	case 1: camera->SetPitch(0);
		camera->SetSpeed(300);
		camera->SetYaw(camera->GetYaw() + (camera->GetSpeed()/25*dt));
		if (startTime < endTime) {
			startTime = time;
			camera->moveRight(dt);
		}
		else {
			movement = 2;
			Vector3 position = fireflies[25]->GetLight()->GetPosition();
			camera->SetPosition(Vector3(position.x,position.y+100,position.z+10));
			startTime = time; endTime = time + 30;
		}
		break;
	case 2:
		camera->SetPitch(0);
		camera->SetYaw(camera->GetYaw() + (camera->GetSpeed()/100 * dt));
		if (startTime < endTime) {
			startTime = time;
			Vector3 position = fireflies[25]->GetLight()->GetPosition();
			camera->SetPosition(Vector3(position.x, position.y + 100, position.z - 20));
		}
		else {
			movement = 0;
			camera->SetPosition(heightMap[0]->GetHeightmapSize() * Vector3(0.5, 7, 0.56));
		}
	}

}


void Renderer::UpdateScene(float dt) {
	camera->UpdateCamera(dt);
	viewMatrix = camera->BuildViewMatrix();

	//frameFrustum.FromMatrix(projMatrix * viewMatrix);
	for (int i = 0; i < 50; i++) {

		fireflies[i]->UpdatePosition(Vector3(rand()%2*10*sin(degree), 0, rand() % 2 * 10*sin(degree)));
	}
	root->Update(dt);

	for (int i = 0; i < 50; i++) {
		fireflies[i]->GetLight()->SetPosition(fireflies[i]->GetWorldTransform().GetPositionVector());
	}
	frameTime -= dt;
	while (frameTime < 0.0f) {
		currentFrame = (currentFrame + 1) % anim->GetFrameCount();
		frameTime += 1.0f / anim->GetFrameRate();
	}

	
}

void Renderer::UpdateWatertime(float time) {
	waterCycle = time/1000;
	waterRotate = time/1000;
	degree = time / 1000;
}

void Renderer::DrawSkybox() {
	glDepthMask(GL_FALSE);
	BindShader(shader[5]);
	UpdateShaderMatrices();

	quad->Draw();
	glDepthMask(GL_TRUE);
}

void Renderer::RenderScene() {

	//BuildNodeLists(root);
	//SortNodeLists();

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//BindShader(shader[0]);


	//UpdateShaderMatrices();
	DrawSkybox();
	DrawNode(root);
}
void Renderer::BuildNodeLists(SceneNode* from) {
	if (frameFrustum.InsideFrustum(*from)) {
		Vector3 dir = from->GetWorldTransform().GetPositionVector() - camera->GetPosition();
		from->SetCameraDistance(Vector3::Dot(dir, dir));
		if (from->GetColour().w < 1.0f) {
			transparentNodeList.push_back(from);
		}
		else {
			nodeList.push_back(from);
		}
	}
	for (vector<SceneNode*>::const_iterator i = from->GetChildIteratorStart(); i != from->GetChildIteratorEnd(); i++) {
		BuildNodeLists((*i));
	}
}

void Renderer::SortNodeLists() {
	std::sort(transparentNodeList.rbegin(), transparentNodeList.rend(), SceneNode::CompareByCameraDistance);
	std::sort(nodeList.begin(), nodeList.end(), SceneNode::CompareByCameraDistance);

}
void Renderer::ClearNodeLists() {
	transparentNodeList.clear();
	nodeList.clear();
}

void Renderer::DrawNodes() {
	for (const auto& i : nodeList) {
		DrawNode(i);
	}
	for (const auto& i : transparentNodeList) {
		DrawNode(i);
	}
}

void Renderer::DrawNode(SceneNode* n) {
	if (n->GetMesh()) {
		modelMatrix = n->GetWorldTransform() * Matrix4::Scale(n->GetModelScale());
		if (n->GetShader()!=NULL) {
			BindShader(n->GetShader());
			UpdateShaderMatrices();
			/*glUniform1i(glGetUniformLocation(n->GetShader()->GetProgram(), "diffuseTex1"), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, terrainTex[0]);

			glUniform1i(glGetUniformLocation(n->GetShader()->GetProgram(), "extraTex1"), 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures_1[0]);
			glUniform1i(glGetUniformLocation(n->GetShader()->GetProgram(), "extraTex2"), 2);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, textures_1[1]);
			glUniform1i(glGetUniformLocation(n->GetShader()->GetProgram(), "extraTex3"), 3);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, textures_1[2]);
			glUniform1i(glGetUniformLocation(n->GetShader()->GetProgram(), "specmap"), 4);
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, specmap[0]);*/

			for (int i = 0; i < 50; i++) {
				std::string s1 = "lightPos[" + std::to_string(i) + "]";
				std::string s2 = "lightColour[" + std::to_string(i) + "]";
				std::string s3 = "lightR[" + std::to_string(i) + "]";
				glUniform3fv(glGetUniformLocation(n->GetShader()->GetProgram(), s1.c_str()),1,(float*)&fireflies[i]->GetLight()->GetPosition());
				glUniform4fv(glGetUniformLocation(n->GetShader()->GetProgram(), s2.c_str()), 1, (float*)&fireflies[i]->GetLight()->GetColour());
				glUniform1f(glGetUniformLocation(n->GetShader()->GetProgram(), s3.c_str()),fireflies[i]->GetLight()->GetRadius());
			}

			Matrix4 invViewProj = (projMatrix * viewMatrix).Inverse();
			glUniformMatrix4fv(glGetUniformLocation(n->GetShader()->GetProgram(), "inverseProjView"), 1, false, invViewProj.values);


			glUniform1i(glGetUniformLocation(n->GetShader()->GetProgram(), "diffuseTex"), 0);
			glUniform3fv(glGetUniformLocation(n->GetShader()->GetProgram(), "cameraPos"), 1, (float*)&camera->GetPosition());
			glUniform1f(glGetUniformLocation(n->GetShader()->GetProgram(), "waterCycle"), waterCycle);
			glUniform1f(glGetUniformLocation(n->GetShader()->GetProgram(), "waterRotate"), waterRotate);
			glUniform4fv(glGetUniformLocation(n->GetShader()->GetProgram(), "nodeColour"), 1, (float*)&n->GetColour());
			glUniform1i(glGetUniformLocation(n->GetShader()->GetProgram(), "useTexture"), 0);


		}
		if (n->GetMesh()->GetSubMeshCount() > 0) {
			vector<Matrix4> frameMatrices;

			const Matrix4* invBindPos = n->GetMesh()->GetInverseBindPose();
			const Matrix4* frameData = anim->GetJointData(currentFrame);

			for (unsigned int i = 0; i < n->GetMesh()->GetJointCount(); i++) {
				frameMatrices.emplace_back(frameData[i] * invBindPos[i]);

			}

			int j = glGetUniformLocation(n->GetShader()->GetProgram(), "joints");
			glUniformMatrix4fv(j, frameMatrices.size(), false, (float*)frameMatrices.data());

			for (int i = 0; i < n->GetMesh()->GetSubMeshCount(); i++) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, matTextures[i]);
				n->GetMesh()->DrawSubMesh(i);
			}
		}else
		n->Draw(*this);
	}
	for (auto i = n->GetChildIteratorStart(); i != n->GetChildIteratorEnd(); i++) {
		DrawNode(*i);
	}
}

//
void Renderer::DrawNode(SceneNode* n, int xPos) {
	if (n->GetMesh()) {
		Matrix4 model = Matrix4::Translation(Vector3(xPos, 0, 0)) * n->GetWorldTransform() * Matrix4::Scale(n->GetModelScale());
		glUniformMatrix4fv(glGetUniformLocation(shader[0]->GetProgram(), "modelMatrix"), 1, false, model.values);
		glUniform4fv(glGetUniformLocation(shader[0]->GetProgram(), "nodeColour"), 1, (float*)&n->GetColour());
		glUniform1i(glGetUniformLocation(shader[0]->GetProgram(), "useTexture"), 0);
		n->Draw(*this);
	}

	for (auto i = n->GetChildIteratorStart(); i != n->GetChildIteratorEnd(); i++) {
		DrawNode(*i, xPos);
	}
}

void Renderer::DrawNode(SceneNode* n, int xPos, int scale) {
	if (n->GetMesh()) {
		Matrix4 model = Matrix4::Translation(Vector3(xPos, 0, 0)) * n->GetWorldTransform() * Matrix4::Scale(n->GetModelScale() + Vector3(scale, scale, scale));
		glUniformMatrix4fv(glGetUniformLocation(shader[0]->GetProgram(), "modelMatrix"), 1, false, model.values);
		glUniform4fv(glGetUniformLocation(shader[0]->GetProgram(), "nodeColour"), 1, (float*)&n->GetColour());
		glUniform1i(glGetUniformLocation(shader[0]->GetProgram(), "useTexture"), 0);
		n->Draw(*this);
	}

	for (auto i = n->GetChildIteratorStart(); i != n->GetChildIteratorEnd(); i++) {
		DrawNode(*i, xPos, scale);
	}
}

void Renderer::UpdateColours(float dt) {
	meshes[0]->UpdateColours(int(dt) % 10);
}


void Renderer::UpdateTextureMatrix(float value) {
	Matrix4 push = Matrix4::Translation(Vector3(-0.5f, -0.5f, 0));
	Matrix4 pop = Matrix4::Translation(Vector3(0.5f, 0.5f, 0));
	Matrix4 rotation = Matrix4::Rotation(value, Vector3(0, 0, 1));
	textureMatrix = pop * rotation * push;
}

void Renderer::ToggleRepeating() {
	repeating = !repeating;
	SetTextureRepeating(textures_1[0], repeating);
}

void Renderer::ToggleFiltering() {
	filtering = !filtering;
	SetTextureFiltering(textures_1[0], filtering);
}


void Renderer::ToggleObject() {
	modifyObject = !modifyObject;
}

void Renderer::MoveObject(float by) {
	positions[(int)modifyObject].z += by;
}

//void Renderer::ToggleBlendMode() {
//	blendMode = (blendMode + 1) % 4;
//	switch (blendMode) {
//	case(0):glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
//	case(1):glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR); break;
//	case(2):glBlendFunc(GL_ONE, GL_ZERO); break;
//	case(3):glBlendFunc(GL_SRC_ALPHA, GL_ONE); break;
//	}
//	std::cout << "mode::" << blendMode << "\n";
//}

void Renderer::ToggleDepthBuffer() {
	depthBuff = !depthBuff;
	glDepthMask(depthBuff);
}

void Renderer::ToggleDepthBufferMode() {
	depthMode = (depthMode + 1) % 8;
	switch (depthMode) {
	case 0: glDepthFunc(GL_NEVER); break;
	case 1: glDepthFunc(GL_LESS); break;
	case 2: glDepthFunc(GL_EQUAL); break;
	case 3: glDepthFunc(GL_LEQUAL); break;
	case 4: glDepthFunc(GL_GREATER); break;
	case 5: glDepthFunc(GL_NOTEQUAL); break;
	case 6: glDepthFunc(GL_GEQUAL); break;
	case 7: glDepthFunc(GL_ALWAYS); break;

	}

	std::cout << "Depth test:" << depthMode << "\n";
}

void Renderer::ToggleDepth() {
	usingDepth = !usingDepth;
	usingDepth ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void Renderer::ToggleAlphaBlend() {
	usingAlpha = !usingAlpha;
	usingAlpha ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
}

void Renderer::SwitchToOrthographic() {
	projMatrix = Matrix4::Orthographic(-1.0f, 10000.0f,
		width / 2.0f, -width / 2.0f, height / 2.0f, -height / 2.0f);
}

void Renderer::SwitchToPerspective() {
	projMatrix = Matrix4::Perspective(1.0f, 15000.0f,
		(float)width / (float)height, 45.0f);
}


