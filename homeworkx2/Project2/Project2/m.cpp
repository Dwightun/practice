#include "1.h"

int main() {
	v_3 vec_1(1, 2, 3);
	v_3 vec_3(3, 2, 1);
	v_3 axis(1, 1, 1);
	float alpha = 30;
	vec_1.print();
	std::cout << "v length = " << vec_1.length() << "\n";
	std::cout << "v length^2 = " << vec_1.square_len() << "\n";
	v_3 vec_2(vec_1);

	std::cout << "Please, write coordinates of new vector\n";
	std::cin >> vec_2;
	std::cout << "sum :" << vec_1 + vec_2 << "\n";
	std::cout << "sub :" << vec_1 - vec_2 << "\n";
	std::cout << "sum (write in vec_2): " << (vec_2 += vec_1) << "\n";
	std::cout << "sub (write in vec_2): " << (vec_2 -= vec_1) << "\n";
	std::cout << "normalize vec_2: " << vec_2.normalize() << "\n";
	std::cout << "getting normal to vec_2: " << vec_2.get_normal() << "\n";
	std::cout << "get new rotated vector(rotate copy of vec): " << vec_3.do_rotate(axis, 90) << "\n";
	std::cout << "rotate vec: " << vec_3.rotate(axis, 90) << "\n";
	std::cout << "vector mult: " << (vec_3 ^ vec_3.get_normal()) << "\n";
	std::cout << "scaler mult: " << (axis * vec_1) << "\n";
	std::cout << "div on scaler: " << (vec_1.div_by_scaler(5)) << "\n";
	std::cout << "mult on scaler: " << (vec_3.mult_by_scaler(5)) << "\n";
	std::cout << "unary minus: " << -vec_3;
}