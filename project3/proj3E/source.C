#include <image.h>
#include <source.h>

Image* Source::GetOutput() {
	return &img;
}

void Source::Update() {
	Execute();
}

