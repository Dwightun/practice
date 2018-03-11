#pragma once

#include<iostream>
#include<cstdlib>
#include<valarray>


using std::istream;
using std::ostream;
using std::string;

class v_3 {
	
private:
	float x;
	float y;
	float z;

public:
	v_3(const float& a, const float& b, const float& c) : x(a), y(b), z(c) {};
	v_3(const v_3& vec) : x(vec.z), y(vec.y), z(vec.z) {};
	~v_3() {};

	v_3 operator+(const v_3& other) const;
	v_3& operator+=(const v_3& other);
	v_3 operator-(const v_3& other) const;
	v_3& operator-();
	v_3& operator-=(const v_3& other);
	float operator*(const v_3& other) const;
	v_3 operator^(const v_3& other) const;

	v_3& mult_by_scaler(const float& scaler);
	v_3& div_by_scaler(const float& scaler);
	v_3& create_normal() const;
	v_3& normalize();
	v_3& rotate(const v_3& axis, const float& theta);
	v_3 get_normal() const;
	v_3 do_rotate(const v_3& axis, const float& theta) const;
	float length() const;
	float square_len() const;
	void print() const;
	bool is_null() const;

	friend ostream& operator<<(ostream& stream, const v_3& vec);
	friend istream& operator>>(istream& stream, v_3& vec);
};