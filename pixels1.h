#pragma once
class pixels1
{
public:
	pixels1(void);
	int get_y();
	int get_cb();
	int get_cr();

	int get_r();
	int get_g();
	int get_b();

	void set_y(int y2);
	void set_cb(int cb2);
	void set_cr(int cr2);

	void set_r(int r2);
	void set_g(int g2);
	void set_b(int b2);
	~pixels1(void);
private:
	int y3;
	int cb3;
	int cr3;
	int r3;
	int g3;
	int b3;
};

