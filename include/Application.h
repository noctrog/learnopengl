#include <glad.h>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <Shader.h>
#include <Camera.h>
#include <Model.h>

namespace sdl2
{
	struct SDL_Deleter
	{
		void operator()(SDL_Window* ptr) { if (ptr) SDL_DestroyWindow(ptr); }
		void operator()(SDL_GLContext* ptr) { if (ptr) SDL_GL_DeleteContext(ptr); }
	};

	using WindowPtr = std::unique_ptr<SDL_Window, SDL_Deleter>;
	using GLContextPtr = std::unique_ptr<SDL_GLContext, SDL_Deleter>;
}

uint32_t load_cubemap(const std::vector<std::string>& faces);

class Application
{
public:
	Application ();
	virtual ~Application ();

	/* Execute application */
	void run(void);

protected:
	virtual void setup_environment(void);
	virtual void setup(void);
	virtual void render(void);
	virtual void close(void);
	virtual void close_environment(void);

private:
	sdl2::WindowPtr window;
	sdl2::GLContextPtr glcontext;

	std::unique_ptr<Shader> box_shader;
	std::unique_ptr<Shader> light_shader;
	std::unique_ptr<Shader> nano_shader;
	std::unique_ptr<Shader> reflect_shader;
	std::unique_ptr<Shader> cubemap_shader;
	std::unique_ptr<Shader> postprocess_shader;
	std::unique_ptr<Model> nanosuit;
	glm::mat4 light_pos;
	glm::vec3 light_color;
	glm::mat4 box_position;

	uint32_t VAO_container, VBO_container;
	uint32_t VAO_light, VBO_light;
	uint32_t VAO_floor, VBO_floor, EBO_floor;
	uint32_t texture, specular_texture, floor_diffuse, floor_specular;

	uint32_t fbo, color_ms_tex, depth_ms_tex, rbo;

	uint32_t VAO_cubemap, VBO_cubemap, texture_cubemap;

	Camera camera_;

};
