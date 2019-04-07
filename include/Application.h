#include <glad.h>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <Shader.h>

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

	std::unique_ptr<Shader> rendering_program;
	uint32_t VAO, VBO, EBO;
	uint32_t texture, smiley_texture;
};
