#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

string getRandomResponse(const vector<string>& responses) {
    if (responses.empty()) return "";
    int index = rand() % responses.size();
    return responses[index];
}

void initializeResponses(map<string, vector<string>>& responses) {
    responses = {
        {"greeting", {
            "Hello! How can I help you today? 😊",
            "Hey there! 👋 What's on your mind?",
            "Hi friend! How can I assist you?",
            "Greetings! Ready to chat?",
            "Welcome back! What can I do for you?"
        }},
        {"how_are_you", {
            "I'm doing great! Thanks for asking 😄",
            "All systems operational! How about you?",
            "Feeling fantastic today! 💪",
            "I'm just peachy! How are you?",
            "Living my best digital life! 😎"
        }},
        {"name", {
            "I'm ChatBoX, your friendly AI assistant!",
            "They call me ChatBoX! 🤖",
            "My name is ChatBoX, at your service!",
            "I go by ChatBoX, your virtual buddy!"
        }},
        {"joke", {
            "Why did the programmer quit his job? Because he didn't get arrays. 😂",
            "Why do Java developers wear glasses? Because they don't C#! 🤓",
            "Why was the computer cold? It forgot to close its Windows. ❄️",
            "How many programmers does it take to change a light bulb? None, that's a hardware problem!",
            "Why don't scientists trust atoms? Because they make up everything!"
        }},
        {"creator", {
            "I was created by a brilliant human developer! 🧠",
            "My creator is a coding wizard! �‍♂️",
            "A talented programmer brought me to life!",
            "I'm the brainchild of an awesome developer team!"
        }},
        {"bye", {
            "Goodbye! Have a wonderful day! 👋",
            "See you later! 😊",
            "Bye for now! Keep smiling! 😄",
            "Farewell! Come back soon!",
            "Until next time! Stay awesome!"
        }},
        {"help", {
            "You can ask me about: my name, tell a joke, get motivation, check time/date, or just chat!",
            "Try asking me: 'Tell me a joke', 'What's your name?', 'How are you?', or 'What can you do?'",
            "I can tell jokes, give advice, tell time, and more! What would you like?"
        }},
        {"weather", {
            "I live in the cloud 🌥️ — it's always perfect here!",
            "It might be sunny in your heart ❤️",
            "Check your window! Or just ask your phone 😄",
            "The weather in my server room is always cool and breezy!",
            "I predict 100% chance of great conversation today!"
        }},
        {"favourite_color", {
            "I love #00FF00 — the color of code! 💚",
            "Blue — like the screen of death... just kidding 😅",
            "I like rainbow colors 🌈 because why pick one?",
            "Binary colors: 0 for black, 1 for white!",
            "All the colors of the terminal spectrum!"
        }},
        {"favourite_food", {
            "Electricity ⚡ and bugs 🐛 (just kidding, I squash them!)",
            "Binary cookies 🍪 — 101010!",
            "I'm a bot, so... data is my delicacy! 🧠",
            "I'm powered by bytes and bits!",
            "My diet consists of pure computational power!"
        }},
        {"motivation", {
            "Believe in yourself! You've got this 💪",
            "Every error is one step closer to success! 🧠",
            "Stay strong. Even infinite loops end someday! 😄",
            "You're capable of amazing things! Keep going!",
            "Remember: every expert was once a beginner!"
        }},
        {"thanks", {
            "You're very welcome! 😊",
            "Happy to help!",
            "Anytime! That's what I'm here for!",
            "No problem at all!",
            "Glad I could assist you!"
        }},
        {"time", {
            "The current time is: TIME_PLACEHOLDER ⏰",
            "Let me check my internal clock... it's TIME_PLACEHOLDER",
            "According to my calculations, it's TIME_PLACEHOLDER",
            "Time you asked: TIME_PLACEHOLDER"
        }},
        {"date", {
            "Today's date is: DATE_PLACEHOLDER 📅",
            "Let me see... it's DATE_PLACEHOLDER today",
            "The calendar shows: DATE_PLACEHOLDER",
            "Mark your calendar: today is DATE_PLACEHOLDER"
        }},
        {"default", {
            "Hmm, I'm not sure I understand. Could you rephrase that? 🤔",
            "I'm still learning! Try asking something else. 📚",
            "That's an interesting question! Maybe try asking differently?",
            "I didn't catch that. Can you ask in another way?",
            "My circuits are a bit confused. Could you clarify?"
        }}
    };
}

string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec;
    return ss.str();
}

string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday;
    return ss.str();
}

string processResponse(const string& category, const map<string, vector<string>>& responses) {
    string response = getRandomResponse(responses.at(category));
    
    if (category == "time") {
        size_t pos = response.find("TIME_PLACEHOLDER");
        if (pos != string::npos) {
            response.replace(pos, 15, getCurrentTime());
        }
    } else if (category == "date") {
        size_t pos = response.find("DATE_PLACEHOLDER");
        if (pos != string::npos) {
            response.replace(pos, 15, getCurrentDate());
        }
    }
    
    return response;
}

string determineCategory(const string& input) {
    if (input == "exit" || input == "bye") return "bye";
    if (input.find("hi") != string::npos || input.find("hey") != string::npos || input.find("hello") != string::npos) return "greeting";
    if (input.find("how are you") != string::npos) return "how_are_you";
    if (input.find("your name") != string::npos) return "name";
    if (input.find("joke") != string::npos) return "joke";
    if (input.find("creator") != string::npos || input.find("made you") != string::npos) return "creator";
    if (input.find("help") != string::npos) return "help";
    if (input.find("weather") != string::npos) return "weather";
    if (input.find("color") != string::npos) return "favourite_color";
    if (input.find("food") != string::npos) return "favourite_food";
    if (input.find("motivate") != string::npos || input.find("advice") != string::npos) return "motivation";
    if (input.find("thank") != string::npos) return "thanks";
    if (input.find("time") != string::npos) return "time";
    if (input.find("date") != string::npos || input.find("day") != string::npos) return "date";
    return "default";
}

int main() {
    srand(time(0));
    map<string, vector<string>> responses;
    initializeResponses(responses);

    cout << "🤖 ChatBoX: Hello! I'm your friendly AI assistant. Type 'bye' or 'exit' to end our chat.\n"
         << "You can ask me about: time, date, jokes, motivation, or just chat!\n" << endl;

    while (true) {
        cout << "👤 You: ";
        string userInput;
        getline(cin, userInput);

        string input = toLower(userInput);
        string category = determineCategory(input);

        if (category == "bye") {
            cout << "🤖 ChatBoX: " << processResponse(category, responses) << endl;
            break;
        }

        cout << "🤖 ChatBoX: " << processResponse(category, responses) << endl;
    }

    return 0;
}
