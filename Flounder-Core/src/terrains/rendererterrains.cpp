#include "rendererterrains.h"

namespace flounder
{
	rendererterrains::rendererterrains() :
		irenderer()
	{
		m_shader = shader::newShader()->addName("terrains")
			->addType(shadertype(GL_VERTEX_SHADER, "res/shaders/terrains/terrainVertex.glsl", loadtype::FILE))
			->addType(shadertype(GL_FRAGMENT_SHADER, "res/shaders/terrains/terrainFragment.glsl", loadtype::FILE))
			->create();
	}

	rendererterrains::~rendererterrains()
	{
		delete m_shader;
	}

	void rendererterrains::render(const vector4 &clipPlane, const icamera &camera)
	{
		prepareRendering(clipPlane, camera);
		renderTerrain(terrains::get()->getTerrain());
		endRendering();
	}

	void rendererterrains::prepareRendering(const vector4 &clipPlane, const icamera &camera)
	{
		// Starts the shader.
		m_shader->start();

		// Loads the uniforms.
		m_shader->loadUniform4fv("projectionMatrix", *camera.getProjectionMatrix());
		m_shader->loadUniform4fv("viewMatrix", *camera.getViewMatrix());
		m_shader->loadUniform4f("clipPlane", clipPlane);

		// Sets the GPU for rendering this object.
		renderer::get()->antialias(display::get()->isAntialiasing());
		renderer::get()->enableDepthTesting();
		renderer::get()->cullBackFaces(true);
	}

	void rendererterrains::renderTerrain(terrain *object)
	{
		// Binds the layouts.
		renderer::get()->bindVAO(object->getVaoID(), 3, 0, 1, 2);

		// Loads the uniforms.
		m_shader->loadUniform4fv("modelMatrix", *object->getModelMatrix());

		m_shader->loadUniform1f("shineDamper", 1.0f);
		m_shader->loadUniform1f("reflectivity", 0.0f);

		// Tells the GPU to render this object.
		renderer::get()->renderElements(GL_TRIANGLES, GL_UNSIGNED_INT, object->getVaoLength());

		// Unbinds the layouts.
		renderer::get()->unbindVAO(3, 0, 1, 2);
	}

	void rendererterrains::endRendering()
	{
		// Stops the shader.
		m_shader->stop();
	}
}