#include "Text.h"
#include <cstring>
#include <iomanip>
#include <cctype>

Text::Text(const char *charSeq)
{
	bufferSize = strlen(charSeq) + 1;
	buffer = new char[bufferSize];
	strcpy(buffer, charSeq);
}

Text::Text(const Text &other)
{
	this->bufferSize = other.bufferSize;
	buffer = new char[bufferSize];
	
	strcpy(buffer, other.buffer);


}


void Text::operator = (const Text &other)
{
	int tempLen = other.getLength();
	
		if (bufferSize < tempLen)
			
		{	
				delete[] buffer;
				bufferSize = tempLen;
				buffer = new char[bufferSize];
		}
	

		
		strcpy(buffer, other.buffer);
}

Text::~Text()
{
	delete[] buffer;
}

int Text::getLength() const
{
	return bufferSize;
}

char Text::operator [] (int n) const
{
	if (buffer[n] == NULL)
		return '\0';
	else
		return buffer[n];
}

void Text::clear()
{
	this->buffer[0] = NULL;
}

void Text::showStructure() const
{
	for (int i = 0; i < bufferSize; i++)
	{
		cout << buffer[i];
	}
	cout << endl;
}

// Look at ascii table, static cast into an int, check against ascii table, and +32/-32 depending on value.
Text Text::toUpper() const
{
	Text temp(buffer);
	for (int i = 0; i < bufferSize; i++) {
		if ((buffer[i] > 96) && (buffer[i] < 123)) {
			temp.buffer[i] = char(buffer[i] - 32);
		}
	}
	return temp;
}

Text Text::toLower() const
{
	Text temp(buffer);
	for (int i = 0; i < bufferSize; i++) {
		if ((buffer[i] > 64) && (buffer[i] < 91)) {
			temp.buffer[i] = char(buffer[i] + 32);
		}
	}
	return temp;
}

bool Text::operator == (const Text& other) const
{
	if (strcmp(this->buffer, other.buffer) == 0)
		return true;
	else
	{
		return false;
	}
}

bool Text::operator <  (const Text& other) const
{
	if (strcmp(this->buffer, other.buffer) < 0)
		return true;

	else
		return false;
}

bool Text::operator >  (const Text& other) const
{
	if (strcmp(this->buffer, other.buffer) > 0)
		return true;

	else
		return false;
}

ostream & operator << (ostream& output, const Text& outputText) {
	cout << outputText.buffer << endl;

	return output;
}

istream & operator >> (istream& input, Text& inputText) {
	cin >> inputText.buffer;

	inputText.bufferSize = strlen(inputText.buffer);

	return input;
}

// Look at ascii table, static cast into an int, check against ascii table, and +32 depending on value.
