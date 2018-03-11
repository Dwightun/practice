#include "1.h"

#define PI 3,14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196442881097566593344612847564823

v_3 v_3::operator+(const v_3& other) const {
	return v_3(x + other.x, y + other.y, z + other.z);
};

v_3& v_3::operator+=(const v_3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
};

v_3 v_3::operator-(const v_3& other) const {
	return v_3(x - other.x, y - other.y, z - other.z);
}

v_3& v_3::operator-=(const v_3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
};

float v_3::operator*(const v_3& other) const {
	return (x*other.x + y * other.y + z * other.z);
};

v_3 v_3::operator^(const v_3& other) const {
	return v_3(y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
};

v_3& v_3::mult_by_scaler(const float& scaler) {
	x = x * scaler;
	y = y * scaler;
	z = z * scaler;
	return *this;
};

v_3& v_3::div_by_scaler(const float& scaler) {
	x = x / scaler;
	y = y / scaler;
	z = z / scaler;
	return *this;
};

void v_3::print() const {
	std::cout << x << " | " << y << " | " << z << "\n" << std::endl;
};

float v_3::length() const {
	return(sqrt((*this) * (*this)));
};

float v_3::square_len() const {
	return (*this) * (*this);
};

v_3 v_3::do_rotate(const v_3& axis, const float& alpha) const {
	float cos_alpha = cos(alpha * PI / 180);
	float sin_alpha = sin(alpha * PI / 180);

	auto new_x = (cos_alpha + (1 - cos_alpha) * axis.x * axis.x) * x
		+ ((1 - cos_alpha) * axis.x * axis.y - sin_alpha * axis.z) * y
		+ ((1 - cos_alpha) * axis.x * axis.z + sin_alpha * axis.y) * z;

	auto new_y = ((1 - cos_alpha) * axis.x * axis.y + sin_alpha * axis.z) * x
		+ (cos_alpha + (1 - cos_alpha) * axis.y * axis.y) * y
		+ ((1 - cos_alpha) * axis.z * axis.y - sin_alpha * axis.x) * z;

	auto new_z = ((1 - cos_alpha) * axis.x * axis.z - sin_alpha * axis.y) * x
		+ ((1 - cos_alpha) * axis.z * axis.y + sin_alpha * axis.x) * y
		+ (cos_alpha + (1 - cos_alpha) * axis.z * axis.z) * z;

	return v_3(new_x, new_y, new_z);
};

v_3& v_3::rotate(const v_3& axis, const float& alpha) {
	*this = this->do_rotate(axis, alpha);
	return *this;
};

v_3& v_3::normalize() {
	if (is_null()) {
		std::cout << "Can't normalize null vector\n";
		x = 0;
		y = 0;
		z = 0;
	}
	else {
		x = x / this->length();
		y = y / this->length();
		z = z / this->length();
	}

	return *this;
};

v_3 v_3::get_normal() const {
	if (is_null()) {
		std::cout << "Can't find normal to null vector\n";
		return v_3(0, 0, 0);
	}
	if (x == 0 && y == 0)
		return v_3(z, 0, 0);
	return v_3(-y, x, 0);
};

ostream& operator<<(ostream& stream, const v_3& vec) {
	stream << vec.x << " " << vec.y << " " << vec.z;
	return stream;
}

istream& operator>>(istream& stream, v_3& vec) {
	stream >> vec.x >> vec.y >> vec.z;
	return stream;
};