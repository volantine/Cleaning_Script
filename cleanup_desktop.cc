#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

// Function to get the extension of a file
std::string getExtension(const fs::path& filePath) {
    return filePath.extension().string();
}

// Function to create a directory if it doesn't exist
void createDirectory(const std::string& directoryPath) {
    if (!fs::exists(directoryPath)) {
        fs::create_directory(directoryPath);
    }
}

// Function to move a file to a specified directory
void moveFile(const fs::path& source, const fs::path& destination) {
    fs::rename(source, destination);
}

// Function to sort and clean up the desktop
void sortDesktop(const std::string& desktopPath) {
    std::vector<std::string> extensionsToFolder = {
        ".txt", ".pdf", ".doc", ".jpg", ".png", ".cpp", ".h", ".zip", ".exe"
        // Add more file extensions and corresponding folders as needed
    };

    for (const auto& file : fs::directory_iterator(desktopPath)) {
        if (fs::is_regular_file(file)) {
            std::string extension = getExtension(file.path());

            auto it = std::find(extensionsToFolder.begin(), extensionsToFolder.end(), extension);
            if (it != extensionsToFolder.end()) {
                std::string folderName = *it;
                createDirectory(desktopPath + "/" + folderName);
                moveFile(file.path(), desktopPath + "/" + folderName + "/" + file.path().filename().string());
            }
        }
    }
}

int main() {
    std::string desktopPath = "/home/student/Desktop";

    std::cout << "Sorting and cleaning up the desktop..." << std::endl;
    sortDesktop(desktopPath);
    std::cout << "Desktop sorted and cleaned up successfully." << std::endl;

    return 0;
}
