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

	size_t last_time = SDL_GetTicks();
	size_t current_time = 0;
	bool b_is_running = true;
	SDL_Event e;
	while (b_is_running) {
		current_time = SDL_GetTicks();
		float delta_time = (float)(current_time - last_time);
		last_time = current_time;

		const uint8_t *k_state = SDL_GetKeyboardState(NULL);
		if (k_state[SDL_SCANCODE_A]) camera_.ProcessKeyboard(LEFT, delta_time);
		if (k_state[SDL_SCANCODE_D]) camera_.ProcessKeyboard(RIGHT, delta_time);
		if (k_state[SDL_SCANCODE_W]) camera_.ProcessKeyboard(FORWARD, delta_time);
		if (k_state[SDL_SCANCODE_S]) camera_.ProcessKeyboard(BACKWARD, delta_time);

		while (SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					b_is_running = false;
					break;
				case SDL_KEYDOWN:
					if (e.key.keysym.sym == SDLK_ESCAPE) b_is_running = false;
					break;
				case SDL_MOUSEMOTION:
					camera_.ProcessMouseMovement(e.motion.xrel, e.motion.yrel);
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
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	
	window.reset(SDL_CreateWindow("GL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_OPENGL));
	if (window == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}

	glcontext = sdl2::GLContextPtr(new SDL_GLContext(SDL_GL_CreateContext(window.get())));

	SDL_GL_SetSwapInterval(2);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	// Init GL
	// Load OpenGL functions (has to be done after context creation)
	if (!gladLoadGL()) {
		exit(-1);
	}
	
	glViewport(0, 0, 1000, 1000);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
}

void Application::setup()
{
	static float vertices[] = {
	    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
                                                                 
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
                                                                 
	    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,-1.0f,  0.0f,  0.0f,
	    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,-1.0f,  0.0f,  0.0f,
	    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,-1.0f,  0.0f,  0.0f,
                                                                 
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
                                                                 
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
                                                                 
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &VAO_container);
	glBindVertexArray(VAO_container);

	glGenBuffers(1, &VBO_container);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_container);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	uint8_t* data = stbi_load("media/container2.png", &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format;
		switch (nrChannels) {
			case 1:
				format = GL_RED;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load image" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &specular_texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specular_texture);
	data = stbi_load("media/container2_specular.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load image" << std::endl;
	}
	stbi_image_free(data);

	box_shader = std::make_unique<Shader>();
	box_shader->loadFromText("./src/shaders/vertex.glsl", "./src/shaders/fragment.glsl");

	glGenVertexArrays(1, &VAO_light);
	glBindVertexArray(VAO_light);

	glGenBuffers(1, &VBO_light);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_light);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	light_shader = std::make_unique<Shader>();
	light_shader->loadFromText("./src/shaders/light_vertex.glsl", "./src/shaders/light_fragment.glsl");

	light_pos = glm::mat4(1.0f);
	light_pos[3] = glm::vec4(-2.0, 0.0, 2.0, 1.0);

	light_color = glm::vec3(1.0f, 1.0f, 1.0f);

	box_position = glm::mat4(1.0f);
}

void Application::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	light_pos[3][0] = 2.0f * cos(SDL_GetTicks()/1000.0f);
	light_pos[3][2] = 2.0f * sin(SDL_GetTicks()/1000.0f);
	light_pos[3][1] = 0.0f + 0.2f * cos(SDL_GetTicks()/100.0f);

	glm::mat4 mvp = glm::perspective(glm::radians(70.0f), 1.0f, 0.1f, 100.0f) * camera_.GetViewMatrix();

	//glm::vec3 light_dir(sin(SDL_GetTicks() * 0.001), cos(SDL_GetTicks() * 0.001), 0.0f);
	// Draw box
	box_shader->use();
	box_shader->setInt("material.diffuse", 0);
	box_shader->setInt("material.specular", 1);
	box_shader->setVec3("viewPos", camera_.Position);
	box_shader->setVec3("material.ambient", 0.1f, 0.1f, 0.11f);
	box_shader->setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
	box_shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	box_shader->setFloat("material.shininess", 32.00f);
	box_shader->setVec3("light.position", light_pos[3]);
	//box_shader->setVec3("light.direction", light_dir);
	box_shader->setVec3("light.ambient", 0.1f * light_color);
	box_shader->setVec3("light.diffuse", 0.5f * light_color);
	box_shader->setVec3("light.specular", light_color);
	box_shader->setFloat("light.constant", 1.0f);
	box_shader->setFloat("light.linear", 0.05f);
	box_shader->setFloat("light.quadratic", 0.04f);

	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvp));

	glBindVertexArray(VAO_container);
	for(int i = 0; i < 10; ++i) {
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(4*cos(0.5*i)*cos(1.2*i), 4*sin(0.4*i)*cos(0.12*i), 4*sin(0.5*i)*cos(0.2*i)));
		float angle = 20 * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	//glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(box_position));
	//glDrawArrays(GL_TRIANGLES, 0, 3 * 2 * 6);

	// Draw light
	light_shader->use();
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvp));
	glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(light_pos));
	light_shader->setVec3("lightColor", light_color);
	glBindVertexArray(VAO_light);
	glDrawArrays(GL_TRIANGLES, 0, 3 * 2 * 6);
}

void Application::close()
{
	glDeleteVertexArrays(1, &VAO_container);
	glDeleteBuffers(1, &VBO_container);
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &specular_texture);
}

void Application::close_environment()
{
	SDL_Quit();
}
