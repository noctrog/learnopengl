#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class direction {
	forwards,
	backwards,
	left,
	right
};

class Camera
{
public:
	Camera( glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = 0.0f, float pitch = 0.0f);
	virtual ~Camera ();

	glm::mat4 get_view_matrix();
	void update_position(direction dir, float delta_time);
	void update_rotation(int x_offset, int y_offset);
	void update_zoom(int offset);
	void update_camera_vectors();

private:
	glm::vec3 position_;
	glm::vec3 front_;
	glm::vec3 up_;
	glm::vec3 right_;
	glm::vec3 worldUp_;

	glm::mat4 projection_matrix_;

	float yaw_, pitch_;

	float movSpeed_, mouseSensivity_, zoom_;
};
