#include "pch.h"
#include "Data.h"

void Data::SetFile(std::string path) {
	m_filePath = path;
	m_manager = FileManager(path);
}