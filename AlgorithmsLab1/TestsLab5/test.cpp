#include "gtest/gtest.h"
#include "../AlgorithmsLab5/MatrixXnX.h"

TEST(Matrix, assignment_operator_rval) {
	MatrixXnX m(3);
	m = MatrixXnX(2);
	EXPECT_EQ(m.GetDim(), 2);
}

TEST(Matrix, assignment_operator_lval_Element_SetElement) {
	MatrixXnX m(3);
	MatrixXnX m2(2);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			m2.SetElement(i, j, i + j);
	m = m2;

	EXPECT_EQ(m.GetDim(), m2.GetDim());
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			EXPECT_EQ(m.Element(i, j), m2.Element(i, j));
}

TEST(Matrix, GetMatrixWithoutStrCol) {
	MatrixXnX m(3);
	for (int i = 0; i < m.GetDim(); i++)
		for (int j = 0; j < m.GetDim(); j++)
			m.SetElement(i, j, i + j);
	/*m:
	0 1 2
	1 2 3
	2 3 4
	*/
	MatrixXnX m00(2);
	m00.SetElement(0, 0, 2);
	m00.SetElement(0, 1, 3);
	m00.SetElement(1, 0, 3);
	m00.SetElement(1, 1, 4);
	EXPECT_TRUE(m00 == m.GetMatrixWithoutStrCol(0, 0));

	MatrixXnX m01(2);
	m01.SetElement(0, 0, 1);
	m01.SetElement(0, 1, 3);
	m01.SetElement(1, 0, 2);
	m01.SetElement(1, 1, 4);
	EXPECT_TRUE(m01 == m.GetMatrixWithoutStrCol(0, 1));

	MatrixXnX m10(2);
	m10.SetElement(0, 0, 1);
	m10.SetElement(0, 1, 2);
	m10.SetElement(1, 0, 3);
	m10.SetElement(1, 1, 4);
	EXPECT_TRUE(m10 == m.GetMatrixWithoutStrCol(1, 0));

	MatrixXnX m11(2);
	m11.SetElement(0, 0, 0);
	m11.SetElement(0, 1, 2);
	m11.SetElement(1, 0, 2);
	m11.SetElement(1, 1, 4);
	EXPECT_TRUE(m11 == m.GetMatrixWithoutStrCol(1, 1));
}

TEST(Matrix, Determinant) {
	MatrixXnX m(3);
	for (int i = 0; i < m.GetDim(); i++)
		for (int j = 0; j < m.GetDim(); j++)
			m.SetElement(i, j, i + j);
	EXPECT_EQ(m.Determinant(), 0);

	m.SetElement(0, 0, 200);
	m.SetElement(0, 2, 12);
	m.SetElement(1, 1, -2);
	m.SetElement(1, 2, 33);
	m.SetElement(2, 1, 12);
	m.SetElement(2, 2, -453);
	EXPECT_EQ(m.Determinant(), 102711);
}

TEST(Matrix, InverseMatrix) {
	MatrixXnX m(3);
	for (int i = 0; i < m.GetDim(); i++)
		for (int j = 0; j < m.GetDim(); j++)
			m.SetElement(i, j, i + j);
	EXPECT_EQ(m.InverseMatrix().GetDim(), 0);

	m.SetElement(0, 0, 200);
	m.SetElement(0, 2, 12);
	m.SetElement(1, 1, -2);
	m.SetElement(1, 2, 33);
	m.SetElement(2, 1, 12);
	m.SetElement(2, 2, -453);

	auto invM = m.InverseMatrix();
	MatrixXnX inv(3);
	inv.SetElement(0, 0, 170.0 / 34237);
	inv.SetElement(0, 1, 199.0 / 34237);
	inv.SetElement(0, 2, 19.0 / 34237);
	inv.SetElement(1, 0, 173.0 / 34237);
	inv.SetElement(1, 1, -30208.0 / 34237);
	inv.SetElement(1, 2, -2196.0 / 34237);
	inv.SetElement(2, 0, 16.0 / 102711);
	inv.SetElement(2, 1, -2398.0 / 102711);
	inv.SetElement(2, 2, -401.0 / 102711);
	EXPECT_TRUE(invM == inv);
}

TEST(Matrix, Transpose) {
	MatrixXnX m(3);
	m.SetElement(0, 0, 1);
	m.SetElement(0, 1, 12);
	m.SetElement(0, 2, 124);
	m.SetElement(1, 0, 45);
	m.SetElement(1, 1, 45);
	m.SetElement(1, 2, 476);
	m.SetElement(2, 0, 123);
	m.SetElement(2, 1, 67);
	m.SetElement(2, 2, 9);
	m.Transpose();

	MatrixXnX trans(3);
	trans.SetElement(0, 0, 1);
	trans.SetElement(0, 1, 45);
	trans.SetElement(0, 2, 123);
	trans.SetElement(1, 0, 12);
	trans.SetElement(1, 1, 45);
	trans.SetElement(1, 2, 67);
	trans.SetElement(2, 0, 124);
	trans.SetElement(2, 1, 476);
	trans.SetElement(2, 2, 9);

	EXPECT_TRUE(m == trans);
}

TEST(Matrix, operatorMult) {
	std::vector<double> v{ 22, 12, 545 };
	MatrixXnX m(3);	
	for (int i = 0; i < m.GetDim(); i++)
		for (int j = 0; j < m.GetDim(); j++)
			m.SetElement(i, j, i + j);

	auto res = m * v;
	EXPECT_TRUE(res[0] == 1102);
	EXPECT_TRUE(res[1] == 1681);
	EXPECT_TRUE(res[2] == 2260);
}