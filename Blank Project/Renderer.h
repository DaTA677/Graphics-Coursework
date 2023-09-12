#pragma once
#include "../nclgl/OGLRenderer.h"
#include "../nclgl/Camera.h"
#include "../nclgl/SceneNode.h"
#include "../nclgl/CubeRobot.h"
#include "../nclgl/Frustum.h"
#include "../nclgl/Firefly.h"

class Mesh;
class MeshAnimation;
class MeshMaterial;

class HeightMap;

#define FIREFLY_COUNT 50

class Renderer : public OGLRenderer {
public:
	Renderer(Window& parent);
	~Renderer(void);

	void UpdateScene(float dt) override;
	void RenderScene() override;

	void SwitchToPerspective();
	void SwitchToOrthographic();

	void ToggleObject();
	void ToggleDepth();
	void ToggleAlphaBlend();
	void ToggleBlendMode();
	void MoveObject(float by);

	void UpdateTextureMatrix(float rotation);
	void ToggleRepeating();
	void ToggleFiltering();
	void ToggleDepthBuffer();
	void ToggleDepthBufferMode();

	void UpdateWatertime(float time);

	void UpdateColours(float dt);

	void DrawSkybox();
	void updateCamera(float time, float dt);

	Camera* GetCamera() const { return camera; }

	SceneNode* GetRoot() { return root; }

protected:
	void DrawNode(SceneNode* n);
	void DrawNode(SceneNode* n, int xPos);
	void DrawNode(SceneNode* n, int xPos, int scale);

	void BuildNodeLists(SceneNode* from);
	void SortNodeLists();
	void ClearNodeLists();
	void DrawNodes();


	SceneNode* root;
	Camera* camera;
	Mesh* cube;
	Mesh* quad;
	Shader* shader[7];

	
	void SetCameraMovement(int i);

	int movement;

	Mesh* meshes[2];
	GLuint textures_1[3];
	GLuint normals_1[3];
	GLuint spec_1[3];
	Vector3 positions[2];

	GLuint textures_2[3];
	GLuint normals_2[3];
	GLuint spec_2[3];

	Frustum frameFrustum;

	vector<SceneNode*> transparentNodeList;
	vector<SceneNode*> nodeList;

	bool modifyObject;
	bool usingDepth;
	bool usingAlpha;
	int blendMode;
	int depthMode;
	bool depthBuff;

	bool filtering;
	bool repeating;

	float waterRotate;
	float waterCycle;

	HeightMap* heightMap[2];
	GLuint terrainTex[2];
	GLuint terrainNor[2];
	GLuint terrainSpec[2];

	GLuint splatmap[2];


	MeshAnimation* anim;
	MeshMaterial* material;
	vector<GLuint> matTextures;

	int currentFrame;
	float frameTime;

	Firefly* fireflies[FIREFLY_COUNT];

	Mesh* sphere;
	
	float degree;

	GLuint cubeMap;

	float startTime;
	float endTime;
};