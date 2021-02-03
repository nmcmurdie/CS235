#include <iostream>
#include <fstream>
#include <sstream>
#include "Set.h"
#include "HashMap.h"
using namespace std;

/** Get effectivity of one Pokemon's moves on another type of Pokemon (0 = ineffective, 1 = effective, 2 = super effective)
    Used to determine winners in battle (Can't be const since not member function) */
int effectivity(Set<string>& effective, Set<string>& ineffective, string type) {
    int effect = 1;
    if (effective.count(type)) effect = 2;
    else if (ineffective.count(type)) effect = 0;
    return effect;
}

int main(int argc, const char * argv[]) {
    // Open Files
    if (argc < 3) {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    
    ifstream in(argv[1]);
    if (!in)  {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    ofstream out(argv[2]);
    // Create all HashMaps to be used later
    HashMap<string, string> pokemon, moves;
    HashMap<string, Set<string>> effectivities, ineffectivities;

    for (string line; getline(in, line); out << endl) {
        istringstream read (line);
        string command, name, type;
        read >> command;

        if (line.size() < 1) continue;
        out << line;
        
        // Read in lots of data to HashMaps
        if (command == "Set:") {
            out << endl << "[";
            Set<string> data;
            for (string itm; read >> itm;) {
                data.insert(itm);
            }
            out << data << "]" << endl;
        }
        else if (command == "Pokemon:") {
            read >> name >> type;
            pokemon[name] = type;
        }
        else if (command == "Move:") {
            read >> name >> type;
            moves[name] = type;
        }
        else if (command == "Effective:") {
            read >> name;
            Set<string> modifiers;
            while (read >> type) modifiers.insert(type);
            effectivities[name] = modifiers;
        }
        else if (command == "Ineffective:") {
            read >> name;
            Set<string> modifiers;
            while (read >> type) modifiers.insert(type);
            ineffectivities[name] = modifiers;
        }
        else if (command == "Battle:") {
            // Retrieve items from HashMap; for actual battle part save effect and opponentEffect as integers to
            // compare them to see who won, then convert the numbers to a string when needed
            string effectString[] = {"ineffective", "effective", "super effective"};
            string opponentName, opponentType;
            Set<string> effective, ineffective;
            
            // Read names & moves (type) for each Pokemon
            read >> name >> type >> opponentName >> opponentType;

            out << endl << name << " (" << type << ") vs " << opponentName << " (" << opponentType << ")" << endl;
            out << name << " is a " << pokemon[name] << " type Pokemon." << endl;
            out << opponentName << " is a " << pokemon[opponentName] << " type Pokemon." << endl;
            out << type << " is a " << moves[type] << " type move." << endl;
            out << opponentType << " is a " << moves[opponentType] << " type move." << endl;
            
            int effect = effectivity(effectivities[moves[type]], ineffectivities[moves[type]], pokemon[opponentName]);
            int opponentEffect = effectivity(effectivities[moves[opponentType]], ineffectivities[moves[opponentType]], pokemon[name]);
            out << type << " is super effective against [" << effectivities[moves[type]] << "] type Pokemon." << endl;
            out << type << " is ineffective against [" << ineffectivities[moves[type]] << "] type Pokemon." << endl;
            out << name << "'s " << type << " is " << effectString[effect] << " against " << opponentName << endl;
            out << opponentType << " is super effective against [" << effectivities[moves[opponentType]] << "] type Pokemon." << endl;
            out << opponentType << " is ineffective against [" << ineffectivities[moves[opponentType]] << "] type Pokemon." << endl;
            out << opponentName << "'s " << opponentType << " is " << effectString[opponentEffect] << " against " << name << endl;
            
            // Use effect numbers to determine the winner
            if (effect == opponentEffect) out << "The battle between " << name << " and " << opponentName << "is a tie." << endl;
            else {
                out << "In the battle between " << name << " and " << opponentName << ", ";
                
                if (effect > opponentEffect) out << name;
                else out << opponentName;
                
                out << " wins!" << endl;
            }
        }
        else if (command == "Pokemon") out << ": " << pokemon;
        else if (command == "Moves") out << ": " << moves;
        else if (command == "Effectivities") out << ": " << effectivities;
        else if (command == "Ineffectivities") out << ": " << ineffectivities;
    }
    
    return 0;
}
