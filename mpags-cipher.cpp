#include <cctype>
#include <iostream>
#include <string>
#include <vector>

// Exercise 5.1
std::string transformChar(char inputChar)
{
    // Convert alphabetic characters to uppercase
    if (std::isalpha(static_cast<unsigned char>(inputChar))) {
        return std::string(1, static_cast<char>(std::toupper(
                                  static_cast<unsigned char>(inputChar))));
    }

    // Transliterate digits to English words
    switch (inputChar) {
        case '0':
            return "ZERO";
        case '1':
            return "ONE";
        case '2':
            return "TWO";
        case '3':
            return "THREE";
        case '4':
            return "FOUR";
        case '5':
            return "FIVE";
        case '6':
            return "SIX";
        case '7':
            return "SEVEN";
        case '8':
            return "EIGHT";
        case '9':
            return "NINE";
        default:
            return "";
    }
}

// Exercise 5.2
bool processCommandLine(const std::vector<std::string>& args,
                        bool& helpRequested, bool& versionRequested,
                        std::string& inputFileName, std::string& outputFileName)
{
    // Get the number of command-line arguments
    const std::size_t nCmdLineArgs{args.size()};

    // Process command-line arguments
    // Ignore the first element (program name)
    for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (args[i] == "-h" || args[i] == "--help") {
            helpRequested = true;

        } else if (args[i] == "--version") {
            versionRequested = true;

        } else if (args[i] == "-i") {
            // Check that a filename follows -i
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                return false;
            } else {
                inputFileName = args[i + 1];
                ++i;
            }

        } else if (args[i] == "-o") {
            // Check that a filename follows -o
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                return false;
            } else {
                outputFileName = args[i + 1];
                ++i;
            }

        } else {
            // Unknown command-line argument
            std::cerr << "[error] unknown argument '" << args[i] << "'\n";
            return false;
        }
    }

    // All arguments processed successfully
    return true;
}

int main(int argc, char* argv[])
{
    // Convert command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};

    // Process command-line arguments using our function
    if (!processCommandLine(cmdLineArgs, helpRequested, versionRequested,
                            inputFile, outputFile)) {
        return 1;
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << std::endl;

        // Help requires no further action
        return 0;
    }

    // Handle version, if requested
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFile.empty()) {
        std::cerr << "[warning] input from file ('" << inputFile
                  << "') not implemented yet, using stdin\n";
    }

    // Loop over each character from user input
    while (std::cin >> inputChar) {
        // Transform the character
        inputText += transformChar(inputChar);
    }

    // Warn that output file option not yet implemented
    if (!outputFile.empty()) {
        std::cerr << "[warning] output to file ('" << outputFile
                  << "') not implemented yet, using stdout\n";
    }

    // Print out the transliterated text
    std::cout << inputText << std::endl;

    // Return 0 to indicate successful execution
    return 0;
}
