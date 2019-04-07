#include <Application.h>
#include <glm/glm.hpp>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

Application::Application()
{

}

Application::~Application()
{

}

void Application::run()
{
	setup_environment();

	setup();

	bool b_is_running = true;
	SDL_Event e;
	while (b_is_running) {
		while (SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					b_is_running = false;
					break;
				case SDL_KEYDOWN:
					if (e.key.keysym.sym == SDLK_ESCAPE) b_is_running = false;
					break;
				default: 
					break;
			}
		}

		render();
		SDL_GL_SwapWindow(window.get());
	}

	close();

	close_environment();
}

void Application::setup_environment()
{
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw std::runtime_error(SDL_GetError());
	}

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	
	window.reset(SDL_CreateWindow("GL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_OPENGL));
	if (window == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}

	glcontext = sdl2::GLContextPtr(new SDL_GLContext(SDL_GL_CreateContext(window.get())));

	SDL_GL_SetSwapInterval(2);

	// Init GL
	// Load OpenGL functions (has to be done after context creation)
	if (!gladLoadGL()) {
		exit(-1);
	}
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_GEQUAL);
	glViewport(0, 0, 1000, 1000);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
}

void Application::setup()
{
	static float vertices[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	static uint32_t elements[] = {
		0, 1, 3,
		1, 2, 3
	};


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, nrChannels;
	uint8_t* data = stbi_load("media/container.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load image" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &smiley_texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, smiley_texture);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("media/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load image" << std::endl;
	}
	stbi_image_free(data);

	rendering_program = std::make_unique<Shader>();
	rendering_program->loadFromText("./src/shaders/vertex.glsl", "./src/shaders/fragment.glsl");
}

void Application::render()
{
	static const float zero = 0.0f;
	glClearBufferfv(GL_DEPTH, 0, &zero);
	rendering_program->use();
	rendering_program->setInt("ourTexture", 0);
	rendering_program->setInt("smiley", 1);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Application::close()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &smiley_texture);
}

void Application::close_environment()
{
	SDL_Quit();
}
