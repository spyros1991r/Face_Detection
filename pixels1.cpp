#include "pixels1.h"


pixels1::pixels1(void)
{
}

int pixels1::get_y()
{
	return y3;
}
int pixels1::get_cb()
{
	return cb3;
}
int pixels1::get_cr()
{
	return cr3;
}
int pixels1::get_r()
{
	return r3;
}
int pixels1::get_g()
{
	return g3;
}
int pixels1::get_b()
{
	return b3;
}

void pixels1::set_y(int y2)
{
	y3 = y2;
}
void pixels1::set_cb(int cb2)
{
	cb3 = cb2;
}
void pixels1::set_cr(int cr2)
{
	cr3 = cr2;
}
void pixels1::set_r(int r2)
{
	r3 = r2;
}
void pixels1::set_g(int g2)
{
	g3 = g2;
}
void pixels1::set_b(int b2)
{
	b3 = b2;
}
pixels1::~pixels1(void)
{
}
