#include <note.h>
#include <string>
#include <chrono>

Noted::Note::Note(std::string note) {
	contents = note;
	created_at = std::chrono::system_clock::now();
};

Noted::Note::Note() : Note("") {};
