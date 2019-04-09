//#include <Camera.h>

//Camera::Camera( glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
	//: position_(pos), up_(up), yaw_(yaw), pitch_(pitch), front_(glm::vec3(0.0f, 0.0f, -1.0f)),
	  //mouseSensivity_(0.1f), movSpeed_(0.05f)
//{
	//projection_matrix_ = glm::perspective(70.0f, 1.0f, 0.1f, 1000.0f);

	//update_camera_vectors();
//}

//Camera::~Camera()
//{

//}

//glm::mat4 Camera::get_view_matrix()
//{
	//return projection_matrix_ * glm::lookAt(position_, position_ + front_, up_);
//}

//void Camera::update_position(direction dir, float delta_time)
//{
	//switch(dir)
	//{
		//case direction::forwards:
			//position_ = position_ + front_ * movSpeed_ * delta_time;
			//break;
		//case direction::backwards:
			//position_ = position_ - front_ * movSpeed_ * delta_time;
			//break;
		//case direction::left:
			//position_ = position_ - right_ * movSpeed_ * delta_time;
			//break;
		//case direction::right:
			//position_ = position_ + right_ * movSpeed_ * delta_time;
			//break;
		//default:
			//break;
	//}
//}

//void Camera::update_rotation(int x_offset, int y_offset)
//{
	//yaw_	+= mouseSensivity_*x_offset;
	//pitch_	+= mouseSensivity_*y_offset;

	////pitch_ = (pitch_ >  89.0f) ?  89.0f : pitch_;
	////pitch_ = (pitch_ < -89.0f) ? -89.0f : pitch_;

	//update_camera_vectors();
//}

//void Camera::update_zoom(int offset)
//{

//}

//void Camera::update_camera_vectors()
//{
	//front_.x = cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
	//front_.y = sin(glm::radians(pitch_));
	//front_.z = cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));

	//front_ = glm::normalize(front_);

	//right_ = glm::normalize(glm::cross(front_, worldUp_));
	//up_    = glm::normalize(glm::cross(right_, front_));
//}
