int func(int n, double d)
{
	int j = n;
	double sum = 0;
	while (j >= 0)
	{
		sum += d;
		-j;
	}
	return sum;
}

int main() {
	func(1, 2);
}