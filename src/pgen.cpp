#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <iostream>
#include <sodium.h>
#include <sodium/randombytes.h>
#include <sodium/utils.h>

struct Alphabet {
  static const std::string lowercase;
  static const std::string uppercase;
  static const std::string numbers;
  static const std::string symbols;
};

const std::string Alphabet::lowercase = "abcdefghijklmnopqrstuvwxyz";
const std::string Alphabet::uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string Alphabet::numbers = "0123456789";
const std::string Alphabet::symbols = "!@#$%^&*()_-+=";

bool hasRequiredCharacters(const std::string &password) {
  return std::any_of(password.begin(), password.end(), ::isupper) &&
         std::any_of(password.begin(), password.end(), ::islower) &&
         std::any_of(password.begin(), password.end(), ::isdigit) &&
         std::any_of(password.begin(), password.end(),
                     [](char c) { return !std::isalnum(c); });
}

std::string generate_password(std::string alphabet, size_t length) {
  if (sodium_init() < 0) {
    std::cout << "Failed to initialize secrets library.";
    return "";
  }

  char password[length + 1];
  size_t alphabet_size = alphabet.size();

  do {
    for (size_t i = 0; i < length; i++) {
      password[i] = alphabet[randombytes_uniform(alphabet_size)];
    }
    password[length] = '\0';
  } while (!hasRequiredCharacters(password));

  return std::string(password);
}

int main(int argc, char *argv[]) {
  // Initialize the CLI app and its options
  CLI::App app{"Generate secure passwords", "pgen"};

  int length = 16;
  std::string use_this_alphabet;

  app.add_option("length", length,
                 "Password length (default: " + std::to_string(length) + ")")
      ->take_last();
  // TODO
  app.add_option("--alphabet,-a", use_this_alphabet, "Use the given alphabet.")
      ->take_last();

  CLI11_PARSE(app, argc, argv);

  if (length < 8) {
    std::cout << "Use at least 8 characters.";
    return 1;
  }

  std::string alphabet = Alphabet::lowercase + Alphabet::uppercase +
                         Alphabet::numbers + Alphabet::symbols;

  std::string generated_password = generate_password(alphabet, length);
  std::cout << "The generated password is: " << generated_password << std::endl;

  sodium_memzero(&generated_password, length);
  return 0;
}
