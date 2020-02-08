int x;
int y;
y = read();
print(y);
x = y - 1;

while (x > 0) {
	y = y * x;
	x = x + -1;
	print(x);
}

print(y);
