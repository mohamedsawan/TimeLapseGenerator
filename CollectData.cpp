#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <fstream>
#include <sstream>
#include "Image.h"
#include <vector>

#define FACTIONS 20 //vanilla 21
#define REGIONS 150 //vanilla 106
#define MAX_TURNS 300
#define MAX_CAMPAIGNS 25
//  #include <opencv>

using namespace std;


struct RGBColor {
    int red;
    int green;
    int blue;
};

struct coordinate {
    int x;
    int y;
};

HANDLE processHandle = NULL;
//VANILLA DATA

/*
string factionMap[] = { "SPQR", "Julii", "Brutii", "Scipii", "Macedon", "Egypt", "Seleucid Empire", "Carthage", "Parthia", "Pontus", "Gaul", "Germania", "Britannia", "Armenia", "Dacia", "Greek Cities", "Numidia", "Scythia", "Spain", "Thrace", "Rebels" };
RGBColor rgbFactionMap[] = { {150, 80, 205}, {165, 20, 20}, {85, 135, 65}, {35, 95, 175}, {0, 0, 0}, {255, 255, 140}, {155, 128, 128}, {255, 255, 255}, {168, 62, 154}, {10, 100, 125}, {77, 95, 45}, {88, 21, 38}, {95, 125, 190}, {32, 115, 85}, {115, 75, 40}, {197, 194, 129}, {55, 80, 90}, {215, 115, 25}, {135, 110, 60}, {115, 195, 195}, {155, 145, 120} };
RGBColor rgbRegionMap[] = { {232, 41, 198}, {232, 41, 55}, {58, 177, 95}, {58, 89, 177}, {177, 170, 58}, {58, 177, 75}, {212, 232, 41}, {177, 58, 83}, {41, 232, 63}, {203, 41, 232}, {131, 33, 125}, {232, 41, 46}, { 41, 162, 232, }, {0, 0, 255}, {232, 198, 41}, {177, 78, 58}, {232, 90, 41}, {131, 89, 33}, {63, 232, 41}, {33, 131, 116}, {232, 41, 135}, {72, 41, 232}, {58, 150, 177}, {33, 100, 131}, {31, 75, 37}, {72, 177, 58}, {230, 41, 232}, {131, 33, 38}, {131, 61, 33}, {17, 74, 202}, {68, 232, 41}, {85, 114, 141}, {199, 31, 143}, {61, 239, 246}, {221, 232, 41}, {13, 198, 117}, {117, 198, 13}, {58, 173, 177}, {218, 246, 61}, {13, 157, 198}, {202, 61, 17}, {61, 177, 58}, {196, 13, 198}, {198, 13, 35}, {157, 13, 198}, {202, 156, 17}, {131, 33, 100}, {157, 198, 13}, {58, 167, 177}, {13, 196, 198}, {198, 43, 13}, {13, 198, 30}, { 0, 0, 255, }, {198, 35, 13}, {52, 13, 198}, {177, 58, 148}, {118, 131, 33}, {202, 17, 122}, {83, 58, 177}, {177, 58, 145}, {17, 165, 202}, {187, 198, 13}, {33, 196, 58}, {198, 13, 174}, {244, 122, 13}, {17, 13, 198}, {33, 59, 131}, {17, 202, 52}, {177, 83, 58}, {41, 232, 225}, {13, 170, 198}, {149, 109, 127}, {177, 58, 167}, {13, 244, 165}, {13, 18, 244}, {58, 177, 106}, {72, 58, 177}, {131, 83, 77}, {225, 192, 192}, {177, 142, 58}, {65, 17, 202}, {202, 126, 17}, {126, 144, 111}, {175, 171, 244}, {33, 131, 128}, {17, 83, 202}, {202, 191, 17}, {198, 178, 13}, {244, 13, 24}, {244, 203, 14}, {131, 33, 77}, {13, 171, 244}, {31, 202, 17}, {193, 162, 206}, {244, 13, 29}, {13, 244, 160}, {244, 13, 138}, {202, 17, 48}, {244, 171, 13}, {244, 13, 214}, {35, 244, 13}, {42, 232, 77}, {122, 13, 244}, { 0, 0, 255, }, {41, 86, 232}, {241, 244, 13} };
string regionMap[] = { "Britannia Inferior","Tribus Saxones","Locus Gepidae","Hyperboria","Tribus Alanni","Tribus Sakae","Hibernia","Tribus Sarmatae","Tribus Silurii","Locus Gothi","Pripet","Britannia Superior","Germania Inferior","The Sea","Tribus Chattii","Regnum Macromannii","Belgica","Maeotis","Agri Decumates","Scythia","Armorica","Germania Superior","Boihaemum","Tribus lazyges","Central Gaul","Dacia","Noricum","Tribus Getae","Pannonia","Bosphorus","Aquitania","Lugdinensis","Colchis","Atropatene","Cisalpine Gaul","Venetia","Transalpine Gaul","Illyria","Thrace","Gallaecia","Armenia","Dalmatia","Narbonensis","Celtiberia","Liguria","Pontus","Paionia","Etruria","Media","Taraconenis","Umbria","Lusitania","The Sea","Sardinia","Latium","Cappadocia","Propontis","Bithynia","Epirus","Macedonia","Galatia","Hispania","Apulia","Campania","Assyria","Baetica","Phrygia","Cilicia","Thessalia","Baliares","Bruttium","Ionia","Babylonia","Syria","Aetolia","Attica","Elymais","Lycia","Peloponnesus","Sicilia Romanus","Sicilia Poeni","Mauretania","Cyprus","Regnum Palmyrae","Phoenicia","Numidia","Africa","Sicilia Graecus","Laconia","Coele Syria","Rhodos","Arabia","Byzacium","Crete","Judaea","Nabataea","Gaetulia","Tripolitania","Cyrenaica","Nile Delta","Sinai","Libya","Middle Egypt","The Sea","Sahara","Thebais" };
string cityMap[] = { "Eburacum", "Bordeshelm", "Domus Dulcis Domus", "Themiskyra", "Campus Alanni", "Campus Sakae", "Tara", "Campus Sarmatae", "Deva", "Vicus Gothi", "Vicus Venedae", "Londinium", "Batavodurum", "sea", "Damme", "Vicus Macromannii", "Samarobriva", "Tanais", "Mogontiacum", "Campus Scythii", "Condate Redonum", "Trier", "Lovosice", "Campus Lazyges", "Alesia", "Porrolissum", "Luvavum", "Campus Getae", "Aquincum", "Chersonesos", "Lemonum", "Lugdunum", "Kotais", "Phraaspa", "Mediolanium", "Patavium", "Massilia", "Segestica", "Tylis", "Asturica", "Artaxarta", "Salona", "Narbo Martius", "Numantia", "Segesta", "Sinope", "Bylazora", "Arrentium", "Arsakia", "Osca", "Ariminum", "Scallabis", "sea", "Caralis", "Rome", "Mazaka", "Byzantium", "Nicomedia", "Apollonia", "Thessalonica", "Ancyra", "Carthago Nova", "Tarrentum", "Capua", "Hatra", "Corduba", "Pergamum", "Tarsus", "Larissa", "Palma", "Croton", "Sardis", "Seleucia", "Antioch", "Thermon", "Athens", "Susa", "Halicarnassus", "Corinth", "Messana", "Lilybaeum", "Tingi", "Salamis", "Palmyra", "Sidon", "Cirta", "Carthage", "Syracuse", "Sparta", "Damascus", "Rhodes", "Dumatha", "Thapsus", "Kydonia", "Jerusalem", "Bostra", "Dimmidi", "Lepcis Magna", "Cyrene", "Alexandria", "Petra", "Siwa", "Memphis", "sea", "Nepte", "Thebes" };
coordinate cityCoordinateMap[] = { {55, 140}, {87, 139}, {135, 139}, {186, 153}, {229, 131}, {248, 152}, {36, 142}, {181, 140}, {48, 139}, {111, 136}, {149, 129}, {57, 128}, {84, 127}, {0, 0}, {95, 130}, {115, 125}, {61, 118}, {190, 114}, {88, 117}, {157, 106}, {46, 113}, {79, 114}, {111, 113}, {131, 106}, {66, 106}, {140, 98}, {99, 104}, {156, 100}, {116, 101}, {175, 95}, {47, 99}, {66, 93}, {216, 91}, {241, 82}, {84, 92}, {94, 90}, {67, 82}, {105, 90}, {150, 83}, {20, 87}, {227, 87}, {118, 75}, {57, 84}, {26, 75}, {83, 84}, {190, 80}, {136, 77}, {91, 80}, {253, 78}, {44, 76}, {96, 82}, {8, 72}, {0, 0}, {79, 57}, {95, 71}, {192, 68}, {160, 73}, {165, 72}, {124, 63}, {138, 68}, {174, 67}, {36, 58}, {114, 63}, {102, 68}, {216, 60}, {17, 58}, {154, 61}, {193, 58}, {136, 59}, {54, 63}, {114, 57}, {162, 57}, {241, 53}, {200, 55}, {132, 55}, {144, 52}, {253, 50}, {158, 49}, {139, 50}, {106, 51}, {94, 48}, {12, 46}, {189, 45}, {212, 46}, {199, 42}, {55, 41}, {82, 45}, {106, 44}, {138, 46}, {205, 43}, {161, 45}, {240, 25}, {83, 34}, {146, 38}, {202, 32}, {213, 27}, {38, 18}, {96, 19}, {130, 19}, {178, 19}, {206, 14}, {166, 2}, {183, 13}, {0, 0}, {61, 1}, {187, 2} };
string unitNames[] = { "barb peasant briton", "barb peasant dacian", "barb peasant gaul", "barb peasant german", "barb peasant scythian", "barb peasant slave", "barb peltast gaul", "barb peltast german", "barb slinger briton", "barb archer dacian", "barb archer scythian", "barb archer slave", "warband archer dacian", "warband archer german", "warband archer scythian", "warband huntsman gaul", "warband hurler briton", "barb infantry briton", "barb infantry dacian", "barb infantry gaul", "barb infantry slave", "warband spear german", "warband sword briton", "warband sword gaul", "warband axe german", "warband axe scythian", "warband falx dacian", "warband falx thracian", "warband dhaxe german", "barb warguard briton", "barb warguard dacian", "barb warguard gaul", "warband woad briton", "barb naked fanatics dacian", "barb naked fanatics gauls", "barb naked fanatics german", "barb naked fanatics slave", "barb naked fanatics spain", "barb druids briton", "barb druids gaul", "barb druids slave", "barb night raiders german", "barb berserker german", "barb screeching women german", "barb wardogs briton", "barb wardogs dacian", "barb wardogs gaul", "barb wardogs german", "barb wardogs scythian", "barb cavalry dacian", "barb cavalry gaul", "barb cavalry german", "barb cavalry scythian", "barb cavalry slave", "barb noble cavalry dacian", "barb noble cavalry gaul", "barb noble cavalry german", "barb noble cavalry slave", "barb gothic cavalry german", "barb chariot light briton", "barb chariot heavy briton", "barb chariot heavy slave", "barb horse archers scythian", "barb horse archers slave", "barb noble horse archers scythian", "barb head hunting maidens scythian", "barb scythian nobles scythian", "barb scythian noblewomen scythian", "barb ballista dacian", "barb onager dacian", "barb onager scythian", "barb chieftain cavalry early dacian", "barb chieftain cavalry early gaul", "barb chieftain cavalry early german", "barb chieftain cavalry early scythian", "barb chieftain cavalry early slave", "barb chieftain cavalry dacian", "barb chieftain cavalry gaul", "barb chieftain cavalry german", "barb british general briton", "barb scythian general scythian", "carthaginian peasant", "carthaginian peltast", "carthaginian slinger", "carthaginian archer", "carthaginian city militia", "carthaginian infantry", "carthaginian medium infantry", "carthaginian heavy infantry", "carthaginian sacred band infantry", "spanish scutarii", "spanish bull warriors", "numidian javelinmen", "numidian desert warriors", "numidian legionaries", "carthaginian cavalry", "carthaginian medium cavalry", "carthaginian general's cavalry early", "carthaginian general's cavalry", "carthaginian royal cavalry", "numidian cavalry", "numidian camel riders", "carthaginian warhounds", "carthaginian elephant forest", "carthaginian elephant african", "carthaginian elephant african cataphract", "carthaginian onager", "carthaginian heavy onager", "east peasant", "east peltast", "east slinger", "east archer", "east hillmen", "east infantry", "east heavy infantry", "east hoplite", "east hoplite brazen shield", "east legionary", "east cavalry", "east heavy cavalry", "east heavy cataphract", "east cappodocian cavalry", "east persian cavalry", "east cataphract archer", "east horse archer", "east camel cataphract", "east elephant", "east scythed chariot", "east chariot archer", "east generals cavalry early", "east generals cavalry", "east pontic general", "east onager", "egyptian peasant", "egyptian peltast", "egyptian slingers", "egyptian archer", "egyptian archer elite", "egyptian nubian spearmen", "egyptian nile infantry", "egyptian infantry", "egyptian elite guards", "egyptian cavalry", "egyptian nubian cavalry", "egyptian cleruch", "egyptian bedouin", "egyptian chariot", "egyptian chariot archer", "egyptian onager", "egyptian heavy onager", "egyptian general's bodyguard early", "egyptian general's bodyguard", "greek peasant", "greek peltast", "greek archer", "greek heavy peltast", "greek hoplite militia", "greek hoplite", "greek hoplite elite", "greek hoplite spartan", "greek levy pikemen", "greek pikemen", "greek royal pikemen", "greek silver shield pikemen", "greek argyraspid", "greek bastarnae", "greek light lancer", "greek cavalry", "greek medium cavalry", "greek heavy cavalry", "greek royal cavalry", "greek general's guard cavalry early", "greek general's guard cavalry", "thracian bodyguard early", "thracian bodyguard", "greek elephant small", "greek elephant african", "greek elephant cataphract", "greek incendiary pigs", "greek ballista", "greek onager", "greek heavy onager", "greek chariot scythed", "roman peasant", "roman archer", "roman archer auxillia", "roman velite", "roman light infantry auxillia", "roman city militia", "roman hastati", "roman princeps", "roman triarii", "roman infantry auxillia", "roman legionary cohort i", "roman legionary first cohort i", "roman legionary cohort ii", "roman legionary first cohort ii", "roman praetorian cohort i", "roman praetorian cohort urban i", "roman arcani", "roman wardogs", "roman pigs", "roman velite gladiator", "roman samnite gladiator", "roman mirmillo gladiator", "roman light cavalry", "roman cavalry auxillia", "roman medium cavalry", "roman heavy cavalry", "roman praetorian cavalry", "roman generals guard cavalry early", "roman generals guard cavalry", "roman ballista", "roman scorpion", "roman onager", "roman heavy onager", "roman repeating ballista", "generic rebel general", "eastern rebel general", "barbarian rebel general", "rebel amazon chariots", "rebel judaean zealots", "merc peltast", "merc illyrian", "merc samnite", "merc cilician pirate", "merc thracian", "merc bastarnae", "merc sarmatian cavalry", "merc horse archers", "merc spanish infantry", "merc eastern infantry", "merc rhodian slingers", "merc cretan archers", "merc greek hoplites", "merc libyan infantry", "merc numidian cavalry", "merc arab cavalry", "merc bedouin", "merc bedouin archers", "merc balearic slingers", "merc barbarian infantry", "merc barbarian cavalry", "merc elephants", "cheat oliphants", "naval biremes", "naval triremes", "naval quinquiremes", "naval corvus quinquireme", "naval deceres", "naval boats", "naval large boats", "naval pirate ships", "barbarian civ peasant", "barbarian female peasant", "carthaginian civ peasant", "carthaginian female peasant", "eastern civ peasant", "eastern female peasant", "egyptian civ peasant", "egyptian female peasant", "greek civ peasant", "greek female peasant", "roman civ peasant", "roman female peasant"};
*/

//RISE OF PERSIA DATA

string factionMap[] = { "Parsa", "Lydia", "Kemet", "Bab-Ilu", "Mada", "Magadha", "Lakedaimon", "Kyrene", "Balkh", "Saba", "Makedon", "Athenaioi", "Phoenicia", "Mazaka", "Autariatai", "Taras", "Kush", "Skudata", "Ionia", "Bessoi", "Autonomoi" };
RGBColor rgbFactionMap[] = { {51, 1, 72}, {10, 100, 125}, {248, 252, 146}, {10, 39, 117}, {23, 85, 6}, {52, 139, 129}, {164, 20, 20}, {78, 132, 17}, {115, 75, 40}, {247, 73, 2}, {0, 0, 0}, {25, 64, 105}, {255, 255, 255}, {184, 101, 25}, {132, 22, 74}, {247, 73, 2}, {132, 22, 74}, {248, 183, 29}, {56, 80, 90}, {66, 104, 147}, {150, 150, 150} };
RGBColor rgbRegionMap[] = { {69, 127, 206}, {107, 156, 168}, {177, 170, 58}, {205, 212, 157}, {58, 177, 75}, {133, 55, 61}, {147, 187, 95}, {155, 255, 167}, {5, 116, 44}, {131, 33, 125}, {1, 128, 187}, {122, 4, 85}, {223, 192, 126}, {199, 3, 174}, {158, 159, 66}, {131, 89, 33}, {162, 97, 102}, {72, 122, 168}, {25, 59, 226}, {192, 137, 84}, {251, 210, 147}, {20, 155, 2}, {143, 83, 7}, {200, 197, 155}, {58, 173, 177}, {250, 128, 151}, {0, 68, 60}, {227, 1, 96}, {159, 17, 28}, {184, 27, 27}, {199, 31, 143}, {188, 46, 46}, {9, 52, 127}, {158, 128, 38}, {72, 177, 58}, {164, 170, 3}, {202, 61, 17}, {61, 177, 58}, {61, 239, 246}, {23, 124, 42}, {18, 34, 188}, {3, 179, 152}, {117, 162, 204}, {238, 239, 158}, {249, 244, 99}, {58, 167, 177}, {177, 78, 58}, {4, 154, 178}, {26, 156, 4}, {134, 246, 128}, {148, 155, 177}, {17, 13, 198}, {1, 217, 162}, {168, 28, 254}, {10, 53, 104}, {211, 44, 67}, {149, 13, 141}, {234, 77, 251}, {172, 244, 168}, {254, 38, 190}, {41, 68, 140}, {177, 58, 148}, {10, 110, 10}, {3, 57, 209}, {194, 218, 61}, {87, 11, 43}, {110, 8, 8}, {88, 250, 235}, {72, 195, 3}, {173, 178, 4}, {90, 254, 38}, {255, 120, 11}, {11, 83, 35}, {189, 99, 3}, {220, 160, 41}, {244, 122, 13}, {8, 114, 138}, {70, 254, 32}, {13, 244, 165}, {33, 100, 131}, {201, 217, 1}, {209, 49, 253}, {109, 9, 115}, {217, 188, 101}, {38, 188, 254}, {7, 149, 12}, {177, 58, 167}, {250, 189, 84}, {143, 55, 7}, {129, 123, 31}, {3, 82, 195}, {121, 9, 69}, {72, 58, 177}, {21, 190, 29}, {222, 134, 246}, {232, 41, 46}, {93, 11, 255}, {9, 127, 88}, {175, 171, 244}, {232, 172, 176}, {11, 93, 52}, {183, 184, 33}, {186, 45, 1}, {223, 189, 1}, {66, 196, 252}, {255, 5, 122}, {83, 11, 61}, {75, 143, 113}, {223, 79, 1}, {33, 131, 128}, {249, 105, 109}, {104, 10, 23}, {49, 141, 38}, {41, 232, 63}, {119, 6, 160}, {244, 203, 14}, {194, 177, 101}, {236, 151, 245}, {244, 13, 29}, {35, 244, 13}, {117, 173, 18}, {104, 184, 119}, {6, 122, 176}, {95, 186, 228}, {13, 171, 244}, {240, 182, 100}, {52, 13, 198}, {70, 38, 254}, {244, 13, 214}, {103, 125, 68}, {205, 173, 88}, {168, 227, 244}, {136, 125, 2}, {13, 244, 160}, {122, 13, 244}, {42, 232, 77}, {212, 232, 41}, {4, 184, 138}, {117, 204, 141}, {241, 244, 13}, {43, 130, 47}, {235, 43, 43}, {71, 147, 50}, {166, 6, 33}, {8, 195, 166}, {86, 99, 121}, {6, 129, 61}, {195, 96, 104}, {180, 181, 33}, {232, 125, 29} };
string regionMap[] = {"Neurai", "Gerrhas", "Sauromatai", "Thyssagetia", "Masaka", "Sogdiana", "Chach", "Yuezhe", "Budinai", "Issedonai", "Tocharia", "Uvarazmiya", "Agathyrsai", "Skythia", "Amyrgia", "Maeotis", "Gandara", "Dacia", "Margus", "Daha", "Albania", "Bakhtris", "Mikra_Skythia", "Bosphoros", "Iapodia", "Breukia", "Taurike", "Kimmeria", "Iberia", "Oseratia", "Kolchis", "Astauene", "Tauris", "Paropamisada", "Getia", "Triballia", "Armina", "Delmatia", "Mattai", "Varkana", "Autariatia", "Haraiva", "Parthyene", "Thatagus", "Pontos_Paralios", "Mada", "Thrake", "Paphlagonia", "Urastu", "Pontos", "Armina_Milid", "Kosala", "Paionia", "Thrake_Bessike", "Bythinia", "Mada_Raga", "Pleraia", "Apoulia", "Thynia", "Anatole", "Zranka", "Kappadokia", "Illyria_Hellenike", "Tsopk", "Assur", "Bisaltia", "Haravautis", "Makedon", "Mysia", "Phrygia", "Kampania", "Kalabria", "Chalkdike", "Troas", "Asagarta", "Assyria", "Leukania", "Kilikia", "Aram", "Kassu", "Epeiros", "Lydia", "Thessale", "Mada_Uvja", "Aiolis", "Brettion", "Babylonia", "Euboia", "Lesbos", "Vatsa", "Lokris", "Pamphylia", "Uvja", "Sind", "Boiotia", "Cedi", "Ionia", "Lykia", "Palmyra", "Persis", "Attike", "Anshan", "Karmana", "Trinakrie_Sikelion", "Achaia", "Argolis", "Karia", "Kypros", "Lakonike", "Phoenikia", "Arabaya_Babirus", "Trinakrie_Tyndaridos", "Chaldea", "Avanti", "Rhodos", "Aram_Damaskos", "Gedrosia", "Krete", "Judaea", "Nabatu", "Mardi", "Gerraei", "Bhojas", "Palestina", "Arabia", "Maketa", "Vindhyacala", "Kyrenaike", "Nile_Delta", "Avaris", "Noba_Lybia", "Libue", "Marmarika", "Nabataea", "Middle_Egypt", "Libya", "Mulaka", "Oasis_Dakhla", "Zufar", "Thebais", "Cera", "Main", "Blemmyae", "Nubia", "Hadramaut", "Kush", "Saba", "Ethiopia", "Qataban", "Azania" };
string cityMap[] = {"Gerros", "Sauromatia", "Thyssagetis", "Massagete", "Maracanda", "Kangha", "Kashgar", "Gelonos", "Issedonia", "Gushan", "Khiva", "Agathirsion", "Olbia", "Amyrgikon", "Tanais", "Taxila", "Klerouchia_Daon", "Merv", "Nisa", "Albana", "Baktra", "Tyras", "Phanagorea", "Metoulon", "Sirmion", "Klerouchia_Tauron", "Pantikapaion", "Mtskheta", "Siskia", "Dioskourios", "Asaak", "Chersonesos", "Kophen", "Istros", "Naissos", "Armavir", "Delminion", "Gazaka", "Zadracarta", "Meteon", "Phra", "Vispauzatis", "Opiana", "Trapezous", "Hagmatana", "Odessos", "Sinope", "Tushpa", "Komana", "Milid", "Atjechatro", "Sardike", "Bessopara", "Heraklea", "Raga", "Epidauros", "Arpoi", "Byzantion", "Ankyra", "Neh", "Pteria", "Epidamnos", "Amid", "Assur_City", "Maroneia", "Paktya", "Aigai", "Daskyleion", "Kelainai", "Poseidonia", "Taras", "Olynthos", "Abydos", "Ysatis", "Nisibis", "Sybaris", "Tarsos", "Khalman", "Bagastana", "Dodone", "Sfard", "Phylake", "Aspadana", "Phokaia", "Rhegion", "Babylon", "Eretria", "Mytilene", "Mathara", "Naupaktos", "Side", "Susim", "Patala", "Thebai", "Ajagomeru", "Miletos", "Telmessos", "Tadmur", "Pathragada", "Athenai", "Ansan", "Harmozia", "Zankle", "Elis", "Argos", "Halikarnassos", "Kityon", "Sparte", "Sidon", "Hira", "Syrakousai", "Ur", "Ujjajni", "Ialysos", "Damascus", "Pura", "Knossos", "Yerushalaim", "Petra", "Taoke", "Gerra", "Bhraukoccha", "Gaza", "Gorda", "Maka", "Bagh", "Kyrene", "Sais", "Tanis", "Noba", "Euesperides", "Paretonion", "Teyma", "Ineb_Hedj", "Amonion", "Bhaja", "Dakhla", "Ubar", "Niwt_Imn", "Belir", "Karna", "Blemmye", "Pselchis", "Sabata", "Meroe", "Mariaba", "Axum", "Tamna", "Opone" };
coordinate cityCoordinateMap[] = { {7, 3}, { 64, 201 }, { 97, 198 }, { 142, 200 }, { 151, 177 }, { 214, 169 }, { 222, 178 }, { 10, 3 }, { 79, 178 }, { 49, 186 }, { 238, 177 }, { 182, 171 }, { 47, 167 }, { 64, 160 }, { 248, 167 }, { 89, 168 }, { 264, 147 }, { 37, 154 }, { 206, 152 }, { 171, 157 }, { 143, 156 }, { 227, 148 }, { 61, 156 }, { 85, 159 }, { 6, 145 }, { 22, 150 }, { 75, 156 }, { 83, 158 }, { 131, 147 }, { 14, 147 }, { 105, 152 }, { 192, 148 }, { 74, 151 }, { 235, 137 }, { 57, 146 }, { 37, 140 }, { 127, 143 }, { 8, 138 }, { 135, 131 }, { 175, 137 }, { 23, 134 }, { 218, 129 }, { 184, 135 }, { 270, 121 }, { 99, 138 }, { 149, 123 }, { 55, 138 }, { 84, 139 }, { 124, 134 }, { 92, 131 }, { 106, 125 }, { 305, 118 }, { 34, 131 }, { 43, 131 }, { 73, 134 }, { 167, 127 }, { 16, 131 }, { 6, 126 }, { 61, 129 }, { 78, 124 }, { 215, 115 }, { 85, 125 }, { 22, 125 }, { 119, 126 }, { 131, 119 }, { 46, 125 }, { 239, 117 }, { 34, 122 }, { 60, 124 }, { 68, 115 }, { 4, 117 }, { 13, 119 }, { 39, 120 }, { 53, 121 }, { 188, 112 }, { 116, 116 }, { 11, 116 }, { 91, 113 }, { 99, 111 }, { 144, 117 }, { 27, 116 }, { 61, 112 }, { 37, 115 }, { 168, 114 }, { 55, 113 }, { 8, 109 }, { 138, 104 }, { 45, 110 }, { 53, 113 }, { 300, 112 }, { 32, 110 }, { 79, 107 }, { 159, 108 }, { 264, 90 }, { 40, 110 }, { 288, 104 }, { 55, 107 }, { 67, 103 }, { 112, 102 }, { 192, 99 }, { 43, 108 }, { 177, 97 }, { 215, 85 }, { 5, 107 }, { 33, 105 }, { 40, 105 }, { 58, 104 }, { 88, 100 }, { 37, 103 }, { 98, 97 }, { 138, 89 }, { 5, 100 }, { 151, 94 }, { 298, 93 }, { 60, 101 }, { 105, 97 }, { 226, 90 }, { 48, 94 }, { 101, 87 }, { 104, 73 }, { 179, 88 }, { 170, 77 }, { 287, 81 }, { 97, 83 }, { 7, 0 }, { 203, 74 }, { 301, 76 }, { 35, 78 }, { 80, 76 }, { 88, 75 }, { 10, 0 }, { 29, 75 }, { 63, 74 }, { 118, 61 }, { 82, 69 }, { 54, 65 }, { 293, 65 }, { 72, 44 }, { 209, 49 }, { 89, 52 }, { 305, 38 }, { 144, 35 }, { 111, 32 }, { 85, 37 }, { 188, 30 }, { 100, 17 }, { 159, 21 }, { 121, 6 }, { 174, 13 }, { 195, 1 } };
string unitNames[] = { "barb peasant briton", "barb peasant dacian", "barb peasant gaul", "barb peasant german", "barb peasant scythian", "barb peasant slave", "barb peltast gaul", "barb peltast german", "barb slinger briton", "barb archer dacian", "barb archer scythian", "barb archer slave", "warband archer dacian", "warband archer german", "warband archer scythian", "warband huntsman gaul", "warband hurler briton", "barb infantry briton", "barb infantry dacian", "barb infantry gaul", "barb infantry slave", "warband spear german", "warband sword briton", "warband sword gaul", "warband axe german", "warband axe scythian", "warband falx dacian", "warband falx thracian", "warband dhaxe german", "barb warguard briton", "barb warguard dacian", "barb warguard gaul", "warband woad briton", "barb naked fanatics dacian", "barb naked fanatics gauls", "barb naked fanatics german", "barb naked fanatics slave", "barb naked fanatics spain", "barb druids briton", "barb druids gaul", "barb druids slave", "barb night raiders german", "barb berserker german", "barb screeching women german", "barb wardogs briton", "barb wardogs dacian", "barb wardogs gaul", "barb wardogs german", "barb wardogs scythian", "barb cavalry dacian", "barb cavalry gaul", "barb cavalry german", "barb cavalry scythian", "barb cavalry slave", "barb noble cavalry dacian", "barb noble cavalry gaul", "barb noble cavalry german", "barb noble cavalry slave", "barb gothic cavalry german", "barb chariot light briton", "barb chariot heavy briton", "barb chariot heavy slave", "barb horse archers scythian", "barb horse archers slave", "barb noble horse archers scythian", "barb head hunting maidens scythian", "barb scythian nobles scythian", "barb scythian noblewomen scythian", "barb ballista dacian", "barb onager dacian", "barb onager scythian", "barb chieftain cavalry early dacian", "barb chieftain cavalry early gaul", "barb chieftain cavalry early german", "barb chieftain cavalry early scythian", "barb chieftain cavalry early slave", "barb chieftain cavalry dacian", "barb chieftain cavalry gaul", "barb chieftain cavalry german", "barb british general briton", "barb scythian general scythian", "carthaginian peasant", "carthaginian peltast", "carthaginian slinger", "carthaginian archer", "carthaginian city militia", "carthaginian infantry", "carthaginian medium infantry", "carthaginian heavy infantry", "carthaginian sacred band infantry", "spanish scutarii", "spanish bull warriors", "numidian javelinmen", "numidian desert warriors", "numidian legionaries", "carthaginian cavalry", "carthaginian medium cavalry", "carthaginian general's cavalry early", "carthaginian general's cavalry", "carthaginian royal cavalry", "numidian cavalry", "numidian camel riders", "carthaginian warhounds", "carthaginian elephant forest", "carthaginian elephant african", "carthaginian elephant african cataphract", "carthaginian onager", "carthaginian heavy onager", "east peasant", "east peltast", "east slinger", "east archer", "east hillmen", "east infantry", "east heavy infantry", "east hoplite", "east hoplite brazen shield", "east legionary", "east cavalry", "east heavy cavalry", "east heavy cataphract", "east cappodocian cavalry", "east persian cavalry", "east cataphract archer", "east horse archer", "east camel cataphract", "east elephant", "east scythed chariot", "east chariot archer", "east generals cavalry early", "east generals cavalry", "east pontic general", "east onager", "egyptian peasant", "egyptian peltast", "egyptian slingers", "egyptian archer", "egyptian archer elite", "egyptian nubian spearmen", "egyptian nile infantry", "egyptian infantry", "egyptian elite guards", "egyptian cavalry", "egyptian nubian cavalry", "egyptian cleruch", "egyptian bedouin", "egyptian chariot", "egyptian chariot archer", "egyptian onager", "egyptian heavy onager", "egyptian general's bodyguard early", "egyptian general's bodyguard", "greek peasant", "greek peltast", "greek archer", "greek heavy peltast", "greek hoplite militia", "greek hoplite", "greek hoplite elite", "greek hoplite spartan", "greek levy pikemen", "greek pikemen", "greek royal pikemen", "greek silver shield pikemen", "greek argyraspid", "greek bastarnae", "greek light lancer", "greek cavalry", "greek medium cavalry", "greek heavy cavalry", "greek royal cavalry", "greek general's guard cavalry early", "greek general's guard cavalry", "thracian bodyguard early", "thracian bodyguard", "greek elephant small", "greek elephant african", "greek elephant cataphract", "greek incendiary pigs", "greek ballista", "greek onager", "greek heavy onager", "greek chariot scythed", "roman peasant", "roman archer", "roman archer auxillia", "roman velite", "roman light infantry auxillia", "roman city militia", "roman hastati", "roman princeps", "roman triarii", "roman infantry auxillia", "roman legionary cohort i", "roman legionary first cohort i", "roman legionary cohort ii", "roman legionary first cohort ii", "roman praetorian cohort i", "roman praetorian cohort urban i", "roman arcani", "roman wardogs", "roman pigs", "roman velite gladiator", "roman samnite gladiator", "roman mirmillo gladiator", "roman light cavalry", "roman cavalry auxillia", "roman medium cavalry", "roman heavy cavalry", "roman praetorian cavalry", "roman generals guard cavalry early", "roman generals guard cavalry", "roman ballista", "roman scorpion", "roman onager", "roman heavy onager", "roman repeating ballista", "generic rebel general", "eastern rebel general", "barbarian rebel general", "rebel amazon chariots", "rebel judaean zealots", "merc peltast", "merc illyrian", "merc samnite", "merc cilician pirate", "merc thracian", "merc bastarnae", "merc sarmatian cavalry", "merc horse archers", "merc spanish infantry", "merc eastern infantry", "merc rhodian slingers", "merc cretan archers", "merc greek hoplites", "merc libyan infantry", "merc numidian cavalry", "merc arab cavalry", "merc bedouin", "merc bedouin archers", "merc balearic slingers", "merc barbarian infantry", "merc barbarian cavalry", "merc elephants", "cheat oliphants", "naval biremes", "naval triremes", "naval quinquiremes", "naval corvus quinquireme", "naval deceres", "naval boats", "naval large boats", "naval pirate ships", "barbarian civ peasant", "barbarian female peasant", "carthaginian civ peasant", "carthaginian female peasant", "eastern civ peasant", "eastern female peasant", "egyptian civ peasant", "egyptian female peasant", "greek civ peasant", "greek female peasant", "roman civ peasant", "roman female peasant" };

uintptr_t GetModuleBaseAddress(char* modName, DWORD procId)
{
    //initialize to zero for error checking
    uintptr_t modBaseAddr = 0;

    //get a handle to a snapshot of all modules
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

    //check if it's valid
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        //this struct holds the actual module information
        MODULEENTRY32 modEntry;

        //this is required for the function to work
        modEntry.dwSize = sizeof(modEntry);

        //If a module exists, get it's entry
        if (Module32First(hSnap, &modEntry))
        {
            //loop through the modules
            do
            {
                //compare the module name against ours
                if (!_stricmp(modEntry.szModule, modName))
                {
                    //copy the base address and break out of the loop
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }

                //each iteration we grab the next module entry
            } while (Module32Next(hSnap, &modEntry));
        }
    }

    //free the handle
    CloseHandle(hSnap);
    return modBaseAddr;
}

/*VOID startup(LPCTSTR lpApplicationName)
{
    // additional information
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // set the size of the structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // start the program up
    CreateProcess(lpApplicationName,   // the path
        (LPSTR)"",        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
    );
    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}*/

void generateMapImage(int ownership[106] , int besieged[106], std::string name)
{
    const char* c = name.c_str();
    Image test("map_regions.tga");
    Image test1("radar_map1.tga");
    Image copy = test1;
    RGBColor temp;
    for (int i = 0; i < copy.w * copy.h * copy.channels; i += copy.channels)
    {
        temp.red = test.data[i];
        temp.green = test.data[i + 1];
        temp.blue = test.data[i + 2];
        for (int j = 0; j < 106; j++)
        {
            if ((temp.red == rgbRegionMap[j].red) && (temp.green == rgbRegionMap[j].green) && (temp.blue == rgbRegionMap[j].blue))
            {
                if (besieged[j] > 0)
                {
                    copy.data[i] = (rgbFactionMap[ownership[j]].red + 255)/2;
                    copy.data[i + 1] = (rgbFactionMap[ownership[j]].green + 255)/2;
                    copy.data[i + 2] = (rgbFactionMap[ownership[j]].blue + 255)/2;
                }
                else 
                {
                    copy.data[i] = rgbFactionMap[ownership[j]].red;
                    copy.data[i + 1] = rgbFactionMap[ownership[j]].green;
                    copy.data[i + 2] = rgbFactionMap[ownership[j]].blue;
                }
                break;
            }
        }
    }
    copy.write(c);

}

double calculateDistance(coordinate city, coordinate army)
{
    int x1 = army.x;
    int y1 = army.y;
    int x2 = city.x;
    int y2 = city.y;

    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)); //Distance formula


}
int findClosestCity(coordinate army)
{
    int closestCity = 0;
    double shortestDistance = calculateDistance(cityCoordinateMap[0], army), distance;
    for (int i = 0; i < REGIONS; i++)
    {
        distance = calculateDistance(cityCoordinateMap[i], army);
        if (shortestDistance > distance)
        {
            shortestDistance = distance;
            closestCity = i;
        }
    }
    return closestCity;
}

int calculateArmySize(int unitAddress)
{
    int armySize = 0, unit, unitList, unitSize, numUnits;
    ReadProcessMemory(processHandle, (LPVOID)(unitAddress + 0x64), &numUnits, sizeof(numUnits), NULL);
    ReadProcessMemory(processHandle, (LPVOID)(unitAddress + 0x5C), &unitList, sizeof(unitList), NULL);
    for (int i = 0; i < numUnits; i++)
    {
        ReadProcessMemory(processHandle, (LPVOID)(unitList + i * 4), &unit, sizeof(unit), NULL);
        ReadProcessMemory(processHandle, (LPVOID)(unit + 0x280), &unitSize, sizeof(unitSize), NULL);
        armySize += unitSize;
    }
    return armySize;
}

void jmpOpCodeToMachineCode(int address, int jmpAdd, int offset, uint8_t arr[5])
{
    jmpAdd = jmpAdd - (address + offset) - 5;
    arr[0] = 0xE9;
    for (int i = 0; i < 4; i++)
    {
        int k = 2 * (3 - i);
        k = (uint8_t)(jmpAdd >> (4 * k));
        arr[4 - i] = k;
    }
}

enum battleType { field, siege, sally, naval };


struct unit
{
    int startSize;
    int endSize;  //soldiers left
    int type;
    int losses;
    std::string unitName;
};

struct army
{
    int armyID;
    int startingSize;
    int soldiersLeft;
    int unitCount;
    coordinate pos;
    int losses;
    bool alive;
    int factionID;
    std::string factionName;
    std::vector <unit> units;
};

struct battle
{
    coordinate pos;
    int winner;   //attacker or defender
    int loser;
    int attackingArmyCount;
    int defendingArmyCount;
    int attackingArmySize;
    int defendingArmySize;
    int numbersAdvantage;
    int battleType;
    int turnNumber;
    bool withdraw;
    std::vector<army> attackingArmies;
    std::vector<army> defendingArmies;
};

struct enemyData
{
    int battles = 0;
    int landBattles = 0;
    int navalBattles = 0;
    int landWins = 0;
    int landLosses = 0;
    int navalWins = 0;
    int navalLosses = 0;
    int siegeAttacks = 0;
    int siegeAttackWins = 0;
    int siegeDefenses = 0;
    int siegeDefenseWins = 0;
    int wins = 0;
    int losses = 0;
    int numbersAdvantage = 0;
    int numbersAdvantageWin = 0;
    int numbersEqual = 0;
    int numbersEqualWin = 0;
    int numbersDisadvantage = 0;
    int numbersDisadvantageWin = 0;
    int settlementsCaptured = 0;
    int settlementsLost = 0;
    int attacks = 0;
    int defends = 0;
};


struct factionData
{
    int battles = 0;
    int landBattles = 0;
    int navalBattles = 0;
    int landWins = 0;
    int landLosses = 0;
    int navalWins = 0;
    int navalLosses = 0;
    int siegeAttacks = 0;
    int siegeAttackWins = 0;
    int siegeDefenses = 0;
    int siegeDefenseWins = 0;
    int wins = 0;
    int losses = 0;
    int drawCount = 0;
    int withdraws = 0;
    int enemyWithdraws = 0;
    int numbersAdvantage = 0;
    int numbersAdvantageWin = 0;
    int numbersEqual = 0;
    int numbersEqualWin = 0;
    int numbersDisadvantage = 0;
    int numbersDisadvantageWin = 0;
    int settlementsCaptured = 0;
    int settlementsLost = 0;
    int attacks = 0;
    int defends = 0;
    int unitTypeCount[265];
    int unitSizeCount[265];
    std::vector<battle> battlesWon;
    std::vector<battle> battlesLost;
    std::vector<battle> draws;
    enemyData eData[FACTIONS+1];
};

void printStatistics(factionData f [FACTIONS+1], ofstream& bData)
{
    for (int i = 1; i < FACTIONS; i++)
    {
        bData << factionMap[i] << " - " << endl;
        bData << "Total Battles: " << f[i].battles << endl;
        bData << "Land Battles: " << f[i].landBattles << endl;
        bData << "Naval Battles: " << f[i].navalBattles << endl;
        bData << "Settlements Captured: " << f[i].settlementsCaptured << endl;
        bData << "Settlements Lost: " << f[i].settlementsLost << endl;
        if (f[i].battles != 0)
            bData << "Total Win %: " << ((double)f[i].wins / (double)f[i].battles) * 100 << "%" << endl;
        if (f[i].landBattles != 0)
            bData << "Land Win %: " << ((double)f[i].landWins / (double)f[i].landBattles) * 100 << "%" << endl;
        if (f[i].navalBattles != 0)
            bData << "Naval Win %: " << ((double)f[i].navalWins / (double)f[i].navalBattles) * 100 << "%" << endl;
        if(f[i].siegeAttacks != 0)
            bData << "Siege Attack Win %: " << ((double)f[i].siegeAttackWins / (double) f[i].siegeAttacks) * 100 << endl; 
        if (f[i].siegeDefenses != 0)
            bData << "Siege Defense Win %: " << ((double)f[i].siegeDefenseWins / (double)f[i].siegeDefenses) * 100 << endl;
        int mostPopularUnit = 0;
        int favoriteUnit = 0;
        for (int j = 0; j < 265; j++)
        {
            if (f[i].unitSizeCount[j] > f[i].unitSizeCount[mostPopularUnit])
            {
                mostPopularUnit = j;
            }
            if (f[i].unitTypeCount[j] > f[i].unitTypeCount[favoriteUnit])
            {
                favoriteUnit = j;
            }
        }
        bData << "Favorite Unit: " << unitNames[favoriteUnit] << endl;
        bData << "Most Popular Unit: " << unitNames[mostPopularUnit] << endl;
        if (f[i].landBattles != 0)
        {
            bData << "Attack %: " << ((double)f[i].attacks / (double)f[i].landBattles) * 100 << "%" << endl;
            bData << "Defend %: " << ((double)f[i].defends / (double)f[i].landBattles) * 100 << "%" << endl;
            bData << "Numbers Advantage: " << f[i].numbersAdvantage << endl;
            if(f[i].numbersAdvantage != 0)
                bData << "Numbers Advantage Win %: " << ((double)f[i].numbersAdvantageWin / (double)f[i].numbersAdvantage) * 100 << "%" << endl;
            bData << "Numbers Equal: " << f[i].numbersEqual << endl;
            if(f[i].numbersEqual != 0)
                bData << "Numbers Equal Win %: " << ((double)f[i].numbersEqualWin / (double)f[i].numbersEqual) * 100 << "%" << endl;
            bData << "Numbers Disadvantage: " << f[i].numbersDisadvantage << endl;
            if(f[i].numbersDisadvantage != 0)
                bData << "Numbers Disadvantage Win %: " << ((double)f[i].numbersDisadvantageWin / (double)f[i].numbersDisadvantage) * 100 << "%" << endl;
        }
        int nemesis[5][2] = { {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0} };

        for (int j = 0; j < FACTIONS; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                if (nemesis[k][1] < f[i].eData[j].battles)
                {
                    int temp1 = nemesis[k][0];
                    int temp2 = nemesis[k][1];
                    int temp3 = j;
                    int temp4 = f[i].eData[j].battles;
                    for (int a = k; a < 5; a++)
                    {
                        if (((k - a) % 2) == 0)
                        {
                            temp1 = nemesis[a][0];
                            temp2 = nemesis[a][1];
                            nemesis[a][0] = temp3;
                            nemesis[a][1] = temp4;
                        }
                        else
                        {
                            temp3 = nemesis[a][0];
                            temp4 = nemesis[a][1];
                            nemesis[a][0] = temp1;
                            nemesis[a][1] = temp2;
                        }
                    }
                    break;
                }
            }
        }

        for (int j = 0; j < 5; j++)
        {
            int ID = nemesis[j][0];
            if (nemesis[j][0] != -1)
            {
                bData << "Nemesis " << j << ": " << factionMap[ID] << ", " << "Total Battles: " << f[i].eData[ID].battles << ", Land Battles: " << f[i].eData[ID].landBattles << ", Naval Battles: " << f[i].eData[ID].navalBattles << ", Settlements Captured: " << f[i].eData[ID].settlementsCaptured << ", Settlements Lost: " << f[i].eData[ID].settlementsLost;
                if (f[i].eData[ID].battles != 0)
                    bData << ", Total Win %: " << ((double)f[i].eData[ID].wins / (double)f[i].eData[ID].battles) * 100;
                if (f[i].eData[ID].landBattles != 0)
                    bData << ", Land Win %: " << ((double)f[i].eData[ID].landWins / (double)f[i].eData[ID].landBattles) * 100;
                if (f[i].eData[ID].navalBattles != 0)
                    bData << ", Naval Win %: " << ((double)f[i].eData[ID].navalWins / (double)f[i].eData[ID].navalBattles) * 100;
                if (f[i].eData[ID].landBattles != 0)
                    bData << ", Attack %: " << ((double)f[i].eData[ID].attacks / (double)f[i].eData[ID].landBattles) * 100;
                if (f[i].eData[ID].landBattles != 0)
                    bData << ", Defend %: " << ((double)f[i].eData[ID].defends / (double)f[i].eData[ID].landBattles) * 100;
                if (f[i].eData[ID].landBattles != 0)
                    bData << ", Numbers Advantage %: " << ((double)f[i].eData[ID].numbersAdvantage / (double)f[i].eData[ID].landBattles) * 100;
                if (f[i].eData[ID].numbersAdvantage != 0)
                    bData << ", Numbers Advantage Win %: " << ((double)f[i].eData[ID].numbersAdvantageWin / (double)f[i].eData[ID].numbersAdvantage) * 100;
                if (f[i].eData[ID].landBattles != 0)
                    bData << ", Numbers Equal %: " << ((double)f[i].eData[ID].numbersEqual / (double)f[i].eData[ID].landBattles) * 100;
                if (f[i].eData[ID].numbersEqual != 0)
                    bData << ", Numbers Equal Win %: " << ((double)f[i].eData[ID].numbersEqualWin / (double)f[i].eData[ID].numbersEqual) * 100;
                if (f[i].eData[ID].landBattles != 0)
                    bData << ", Numbers Disadvantage %: " << ((double)f[i].eData[ID].numbersDisadvantage / (double)f[i].eData[ID].landBattles) * 100;
                if (f[i].eData[ID].numbersDisadvantage != 0)
                    bData << ", Numbers Disadvantage Win %: " << ((double)f[i].eData[ID].numbersDisadvantageWin / (double)f[i].eData[ID].numbersDisadvantage) * 100;
                bData << endl;
            }
        }

        bData << "--------------------------------------------------------------------------------------------------------" << endl;
    }
}

int main()
{
    int nemesis[5][2] = { {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0} };
    int arr[5] = { 3, 7, 0, 1 };

    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            if (nemesis[k][1] < arr[j])
            {
                int temp1 = nemesis[k][0];
                int temp2 = nemesis[k][1];
                int temp3 = j;
                int temp4 = arr[j];
                for (int a = k; a < 5; a++)
                {
                    if (((k - a) % 2) == 0)
                    {
                        temp1 = nemesis[a][0];
                        temp2 = nemesis[a][1];
                        nemesis[a][0] = temp3;
                        nemesis[a][1] = temp4;
                    }
                    else
                    {
                        temp3 = nemesis[a][0];
                        temp4 = nemesis[a][1];
                        nemesis[a][0] = temp1;
                        nemesis[a][1] = temp2;
                    }
                }
                break;
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
   //     cout << "ID: " << nemesis[i][0] << " battles: " << nemesis[i][1] << endl;
    }
    int campaigns = 1;
    while (campaigns <= MAX_CAMPAIGNS)
    {

        factionData fData[FACTIONS+1];
        //char gameName[] = "RomeTW.exe";
        char gameName[] = "Total War ROME REMASTERED.exe";

        ofstream myfile;
        ofstream rawData;
        ofstream battleData;
        ofstream battleDat;
        myfile.open("example.txt");
        stringstream out;
        out << "Campaign Data/Raw Data" << campaigns << ".txt";
        string s = out.str();
        const char* fname = s.c_str();
        rawData.open(fname);
        out.str("");
        out << "Campaign Data/Battle Data" << campaigns << ".txt";
        s = out.str();
        fname = s.c_str();
        battleData.open(fname);
        out.str("");
        out << "Campaign Data/Battle" << campaigns << ".txt";
        s = out.str();
        fname = s.c_str();
        battleDat.open(fname);
        //  system("C:/Users/mohamed sawan/Desktop/Rome - Total War/RomeTW.exe");
          //system("\s"C:\\Users\\mohamed sawan\\Desktop\\Rome - Total War\\RomeTW.exe\"");
          //system("pause");
        int diplomacyMap[20][20];
        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 20; j++)
                diplomacyMap[i][j] = 200;

        for (int i = 0; i < FACTIONS; i++)
        {
            for (int j = 0; j < 264; j++)
            {
                fData[i].unitSizeCount[j] = 0;
                fData[i].unitTypeCount[j] = 0;
            }
        }

        //VANILLA DATA
        int regionOwnerMap[] = { 12, 20, 20, 20, 17, 8, 20, 17, 12, 20, 20, 12, 11, -1, 11, 11, 12, 17, 11, 17, 10, 11, 20, 14, 10, 14, 20, 19, 20, 20, 10, 20, 13, 20, 10, 10, 20, 20, 19, 18, 13, 20, 10, 10, 20, 9, 4, 0, 8, 18, 0, 18, -1, 7, 3, 9, 20, 20, 20, 4, 20, 7, 1, 2, 6, 7, 15, 6, 4, 7, 1, 6, 6, 6, 15, 20, 8, 20, 4, 2, 7, 16, 5, 20, 5, 16, 7, 15, 15, 6, 15, 20, 7, 20, 5, 20, 16, 20, 20, 5, 20, 16, 5, -1, 20, 5 };
        int besiegedMap[REGIONS];
        for (int i = 0; i < REGIONS; i++)
            besiegedMap[i] = 0;

        //generateMapImage(regionOwnerMap, "test\\test.png");
        //while (true);
        //HWND hGameWindow = FindWindow(NULL, "Rome: Total War");
        HWND hGameWindow = FindWindow(NULL, "Total War: ROME REMASTERED");
        if (hGameWindow == NULL)
        {
            std::cout << "Waiting to start the game!" << std::endl;
            ShellExecute(NULL, "open", "C:/Program Files (x86)/Steam/steamapps/common/Rome Total War Gold/RomeTW.exe", " -nm -ne -strat:imperial_campaign -multirun -na", NULL, SW_SHOWDEFAULT);
            while (hGameWindow == NULL)
            {
                hGameWindow = FindWindow(NULL, "Rome: Total War");
            }
        }
        cout << "got it" << endl;
        DWORD pID = NULL;
        GetWindowThreadProcessId(hGameWindow, &pID);
        processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
        if (processHandle == INVALID_HANDLE_VALUE || processHandle == NULL)
        {
            cout << "Failed to open process" << endl;
            return 0;
        }
        DWORD stadd = 0x162a62c;
        string regnam;
        std::stringstream ss;
        char ttc[32];
        int ex, wy;
        uint8_t red, green, blue;
        //int cc = atoi(ss);
  //      uint8_t n = 0xeb;
//        WriteProcessMemory(processHandle, (LPVOID)0xde7cd3, &n, sizeof(n), NULL);
        uintptr_t gameBaseAddress = GetModuleBaseAddress((gameName), pID);
        /*---------
        * VANILLA DATA (RTW MAIN .EXE DATA??)
        *----------*/
        DWORD offsetGameToBaseAddress = 0x024D99D4;
        DWORD baseAddress = gameBaseAddress + offsetGameToBaseAddress;
        DWORD diplomacyAddress = gameBaseAddress + 0x24CCD98;
        DWORD turnNumberAddress = gameBaseAddress + 0x24CCAB8;
        DWORD isCampaignStartAddress = gameBaseAddress + 0xED08D4; // 0x24E1388;
        DWORD factionBaseAddress = 0x28CC9D4 + 0x54;
        DWORD regionBaseAddress = 0x28D99D4;
        DWORD unitsBaseAddress = 0x1589644;
        DWORD currFactionAdd = 0x28CCA98;
        DWORD toggleFastMovementAdd = 0x28F15F0;
        DWORD battleInfoAddress = 0x18DC3AC;
        int dip = 0x984;

        /*---------
        * ROP DATA (RTW ATLERNATE .EXE FILE??)
        *----------*
        DWORD offsetGameToBaseAddress = 0x162A62C; //region address
        DWORD diplomacyAddress = 0x161D9F0;
        DWORD turnNumberAddress = 0x161D710;
        DWORD isCampaignStartAddress = 0x010276EC;
        DWORD factionBaseAddress = 0x161D62C + 0x54;
        DWORD regionBaseAddress = 0x162A62C;
        DWORD unitsBaseAddress = 0x1589644;
        DWORD currFactionAdd = 0x161D6F0;
        DWORD toggleFastMovementAdd = 0x1642248;
        int dip = 0x984;
        int dip2 = 0x74;
        DWORD battleInfoAddress = 0x1672624;
        int orderMap[20] = {11, 15, 17, 14, 10, 13, 0, 1, 12, 16, 5, 3, 22, 9, 7, 2, 18, 8, 6, 19};
        */

       

        DWORD currFaction;
        DWORD isBesieged;
        int turnNumber, f, m = -1;
        int isCampaignStart, mainFaction, secondFaction;
        int signalAddress = 0x28e1ca8;
        int signalValue;
        int defValue = 162;
        std::vector<battle> battles;
        uint8_t preBattleJmp[5];
        uint8_t postBattleJmp[5];
        uint8_t injection1[35] = { 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0xEC, 0x01, 0x00, 0x00, 0x50, 0xB8, 0xA8, 0x1C, 0x8E, 0x02, 0xC7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x38, 0xA2, 0x00, 0x00, 0x00, 0x75, 0xF8, 0x58, 0xE9, 0x00, 0x00, 0x00, 0x00 };
        uint8_t injection2[32] = { 0x31, 0xC0, 0x83, 0x7D, 0x84, 0x00, 0x50, 0xB8, 0xA8, 0x1C, 0x8E, 0x02, 0xC7, 0x00, 0x01, 0x00, 0x00, 0x00, 0x81, 0x38, 0xA2, 0x00, 0x00, 0x00, 0x75, 0xF8, 0x58, 0xE9, 0x60, 0xC2, 0x52, 0xFD };
        int add1 = 0x60978E;
        int add2 = 0x4CC288;
        int tempV = 162;
        WriteProcessMemory(processHandle, (LPVOID)signalAddress, &tempV, sizeof(tempV), NULL);
        LPVOID addJmp1 = VirtualAllocEx(processHandle, NULL, 4192, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        LPVOID addJmp2 = VirtualAllocEx(processHandle, NULL, 4192, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        int jmp1 = (int)addJmp1;
        uint8_t* a;
        jmpOpCodeToMachineCode(0x609785, (int)addJmp1, 0, preBattleJmp);
        jmpOpCodeToMachineCode((int)addJmp1, add1, 0x1E, (injection1 + 30));

        jmpOpCodeToMachineCode(0x4CC282, (int)addJmp2, 0, postBattleJmp);
        jmpOpCodeToMachineCode((int)addJmp2, add2, 0x1B, (injection2 + 27));

        WriteProcessMemory(processHandle, (LPVOID)0x609785, &preBattleJmp, sizeof(preBattleJmp), NULL);
        WriteProcessMemory(processHandle, addJmp1, &injection1, sizeof(injection1), NULL);

        WriteProcessMemory(processHandle, (LPVOID)0x4CC282, &postBattleJmp, sizeof(postBattleJmp), NULL);
        WriteProcessMemory(processHandle, addJmp2, &injection2, sizeof(injection2), NULL);
        ReadProcessMemory(processHandle, (LPVOID)(isCampaignStartAddress), &isCampaignStart, sizeof(isCampaignStart), NULL);
        DWORD value;
        DWORD diplomacy;
        int unitName;
        char name[49];
        while (isCampaignStart <= 0)
        {
            ReadProcessMemory(processHandle, (LPVOID)(isCampaignStartAddress), &isCampaignStart, sizeof(isCampaignStart), NULL);
            ReadProcessMemory(processHandle, (LPVOID)(factionBaseAddress), &f, sizeof(f), NULL);
            ReadProcessMemory(processHandle, (LPVOID)(f + 0x504), &m, sizeof(m), NULL);
        }
        /*
        cout << "{";
        for (int i = 0; i < 265; i++)
        {
            ReadProcessMemory(processHandle, (LPVOID)(unitsBaseAddress + i*0x20C), &unitName, sizeof(unitName), NULL);
            ReadProcessMemory(processHandle, (LPVOID)(unitName), &name, 0x29, NULL);
            cout << "\"" << name << "\", ";
        }
        cout << "}";*/
        cout << "GOT IT " << endl;
        int isAlive = 2;
        int fast = 0x100;
        ReadProcessMemory(processHandle, (LPVOID)(turnNumberAddress), &turnNumber, sizeof(turnNumber), NULL);
        ReadProcessMemory(processHandle, (LPVOID)(factionBaseAddress + 3 * 4), &mainFaction, sizeof(mainFaction), NULL);
        ReadProcessMemory(processHandle, (LPVOID)(factionBaseAddress + 4), &secondFaction, sizeof(secondFaction), NULL);
        WriteProcessMemory(processHandle, (LPVOID)(toggleFastMovementAdd), &fast, sizeof(fast), NULL);
       // WriteProcessMemory(processHandle, (LPVOID)(mainFaction + 0x178), &isAlive, sizeof(isAlive), NULL);  //tells game faction is destroyed, but doesn't activate end game pop up. means game will ignore faction and game will continue even if faction is destroyed
        int temp = -1;
        while (turnNumber < MAX_TURNS)
        {
            if(turnNumber == 250)
                WriteProcessMemory(processHandle, (LPVOID)(mainFaction + 0x178), &isAlive, sizeof(isAlive), NULL);
            ReadProcessMemory(processHandle, (LPVOID)(turnNumberAddress), &turnNumber, sizeof(turnNumber), NULL);
            ReadProcessMemory(processHandle, (LPVOID)(currFactionAdd), &currFaction, sizeof(currFaction), NULL);
            if /*(currFaction == firstFaction)*/ (turnNumber > temp)
            {
                temp = turnNumber;
                rawData << "." << turnNumber << ":" << endl;
                battleData << "." << turnNumber << ":" << endl;
                int owner;
                for (int i = 0; i < REGIONS; i++)
                {
                    ReadProcessMemory(processHandle, (LPVOID)(regionBaseAddress + i * 0x1D8), &owner, sizeof(owner), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(owner + 0xA0), &owner, sizeof(owner), NULL);
                    rawData << owner << " ";
                }
                rawData << endl;
                for (int i = 0; i < FACTIONS - 1; i++)
                {
                    for (int j = 0; j < FACTIONS - 1; j++)
                    {
                        ReadProcessMemory(processHandle, (LPVOID)(diplomacyAddress + (i * dip) + (j * 0x74) + 4), &diplomacy, sizeof(diplomacy), NULL);
                        if ((diplomacy == 600) && (diplomacyMap[i][j] != 600) && (i < j))
                        {
                            rawData << i << "W" << j << " ";
                        }
                        if ((diplomacy != 600) && (diplomacyMap[i][j] == 600) && (i < j))
                        {
                            rawData << i << "P" << j << " ";
                        }
                        if ((diplomacy == 0) && (diplomacyMap[i][j] != 0) && (i < j))
                        {
                            rawData << i << "A" << j << " ";
                        }
                        diplomacyMap[i][j] = diplomacy;
                    }
                }
                rawData << endl;

                for (int i = 0; i < REGIONS; i++)
                    besiegedMap[i] = -1;
                for (int i = 0; i < FACTIONS - 1; i++)
                {
                    int fp, factionNumber, characters, money, regions, charList, cityList;
                    ReadProcessMemory(processHandle, (LPVOID)(factionBaseAddress + 4 * i), &fp, sizeof(fp), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(fp + 0xF0), &characters, sizeof(characters), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(fp + 0xA0), &factionNumber, sizeof(factionNumber), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(fp + 0x114), &regions, sizeof(regions), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(fp + 0x504), &money, sizeof(money), NULL);
                    rawData << factionNumber << ": ";
                    rawData << regions << ", ";
                    rawData << money << ", [";
                    ReadProcessMemory(processHandle, (LPVOID)(fp + 0xE8), &charList, sizeof(charList), NULL);
                    bool armyFlag = false;
                    for (int j = 0; j < characters; j++)
                    {
                        int ch, isBesieging, armyInfo, x, y, numUnits;
                        ReadProcessMemory(processHandle, (LPVOID)(charList + j * 4), &ch, sizeof(ch), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(ch + 0xC), &x, sizeof(x), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(ch + 0x10), &y, sizeof(y), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(ch + 0xE4), &armyInfo, sizeof(armyInfo), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(armyInfo + 0x64), &numUnits, sizeof(numUnits), NULL);
                        if (armyInfo != 0)
                        {
                            int unitList, unit, unitID;
                            ReadProcessMemory(processHandle, (LPVOID)(armyInfo + 0x5C), &unitList, sizeof(unitList), NULL);
                            int size = calculateArmySize(armyInfo);
                            int garrison = 0; //not a garrison
                            int sea;
                            ReadProcessMemory(processHandle, (LPVOID)(ch + 0xEC), &sea, sizeof(sea), NULL);
                            if (sea == 0)
                                sea = 1;
                            else
                                sea = 0;
                            rawData << "{" << garrison << ", " << sea << ", " << size << ", " << numUnits << ", ";
                            rawData << "{";
                            for (int n = 0; n < numUnits; n++)
                            {
                                ReadProcessMemory(processHandle, (LPVOID)(unitList + n * 4), &unit, sizeof(unit), NULL);
                                ReadProcessMemory(processHandle, (LPVOID)(unit + 0x50), &unitID, sizeof(unitID), NULL);
                                ReadProcessMemory(processHandle, (LPVOID)(unitID + 0x8), &unitID, sizeof(unitID), NULL);
                                rawData << unitID << ", ";

                            }
                            rawData.seekp(-1, std::ios_base::cur);
                            rawData.seekp(-1, std::ios_base::cur);
                            rawData << "}, ";
                            rawData << "{" << x << ", " << y << "}}, ";
                            armyFlag = true;
                            ReadProcessMemory(processHandle, (LPVOID)(armyInfo + 0xC8), &isBesieging, sizeof(isBesieging), NULL);
                            if (isBesieging != 0)
                                besiegedMap[findClosestCity({ x, y })] = factionNumber;
                        }

                    }
                    ReadProcessMemory(processHandle, (LPVOID)(fp + 0x10C), &cityList, sizeof(cityList), NULL);
                    for (int j = 0; j < regions; j++)
                    {
                        int city, armyInfo, x, y, numUnits;
                        ReadProcessMemory(processHandle, (LPVOID)(cityList + j * 4), &city, sizeof(city), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(city + 0xC), &x, sizeof(x), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(city + 0x10), &y, sizeof(y), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(city + 0x40), &armyInfo, sizeof(armyInfo), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(armyInfo + 0x64), &numUnits, sizeof(numUnits), NULL);
                        if (armyInfo != 0)
                        {
                            int unitList, unit, unitID;
                            ReadProcessMemory(processHandle, (LPVOID)(armyInfo + 0x5C), &unitList, sizeof(unitList), NULL);
                            int size = calculateArmySize(armyInfo);
                            int garrison = 1; //is a garrison
                            rawData << "{" << garrison << ", " << size << ", " << numUnits << ", ";
                            rawData << "{";
                            for (int n = 0; n < numUnits; n++)
                            {
                                ReadProcessMemory(processHandle, (LPVOID)(unitList + n * 4), &unit, sizeof(unit), NULL);
                                ReadProcessMemory(processHandle, (LPVOID)(unit + 0x50), &unitID, sizeof(unitID), NULL);
                                ReadProcessMemory(processHandle, (LPVOID)(unitID + 0x8), &unitID, sizeof(unitID), NULL);
                                rawData << unitID << ", ";

                            }
                            rawData.seekp(-1, std::ios_base::cur);
                            rawData.seekp(-1, std::ios_base::cur);
                            rawData << "}, ";
                            rawData << "{" << x << ", " << y << "}}, ";
                            armyFlag = true;
                        }
                        if (armyInfo == 0)
                        {
                            rawData << "{1, 0, 0, 0, {}, {" << x << ", " << y << "}}, ";
                            armyFlag = true;
                        }

                    }
                    if (armyFlag)
                    {
                        rawData.seekp(-1, std::ios_base::cur);
                        rawData.seekp(-1, std::ios_base::cur);
                    }

                    rawData << "], {";
                    int k = 0;
                    for (int j = 0; j < 20; j++)
                    {
                        int r = j;
                        //if (j < 4)
                         //   r = (j + 1) % 4;
                        ReadProcessMemory(processHandle, (LPVOID)(diplomacyAddress + (factionNumber * dip) + (r * 0x74) + 4), &diplomacy, sizeof(diplomacy), NULL);
                        if (diplomacy == 600 && (k == 0))
                        {
                            rawData << r;
                            k++;
                        }
                        else if (diplomacy == 600)
                            rawData << ", " << r;
                    }
                    rawData << "}, ";

                    rawData << "{";
                    k = 0;
                    for (int j = 0; j < 20; j++)
                    {
                        int r = j;
                     //   if (j < 4)
                     //       r = (j + 1) % 4;
                        ReadProcessMemory(processHandle, (LPVOID)(diplomacyAddress + (factionNumber * dip) + (r * 0x74) + 4), &diplomacy, sizeof(diplomacy), NULL);
                        if (diplomacy == 0 && (r != factionNumber) && (k == 0))
                        {
                            rawData << r;
                            k++;
                        }
                        else if (diplomacy == 0 && (r != factionNumber))
                            rawData << ", " << r;
                    }
                    rawData << "}";
                    rawData << endl;

                }
                for (int i = 0; i < REGIONS; i++)
                {
                    rawData << besiegedMap[i] << " ";
                }
                rawData << endl;

                if (turnNumber == MAX_TURNS)// || 1)
                {
                    for (int i = 0; i < FACTIONS; i++)
                    {
                        int r = i;
                      //  if (i == 0)
                        //    r = 3;
                      //  if ((i > 0) && (i <= 3))
                       // {
                       //     r = i - 1;
                       // }
                        int battleInfo, faction, off1 = 1, off2 = 1, fNum;
                        ReadProcessMemory(processHandle, (LPVOID)(factionBaseAddress + 4 * r), &faction, sizeof(faction), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(faction + 0x898), &battleInfo, sizeof(battleInfo), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(faction + 0xA0), &fNum, sizeof(fNum), NULL);
                        rawData << fNum << "{";
                        for (int j = 0; j < FACTIONS; j++)
                        {
                            int wins, losses;
                            ReadProcessMemory(processHandle, (LPVOID)(battleInfo + (j * 4 * 3)), &wins, sizeof(wins), NULL);
                            ReadProcessMemory(processHandle, (LPVOID)(battleInfo + (j * 4 * 3) + 4), &losses, sizeof(losses), NULL);
                            rawData << "{" << wins << ", " << losses << "}, ";
                            if (j == FACTIONS - 1)
                                rawData.seekp(-2, std::ios_base::cur);
                        }
                        rawData << "}";
                        rawData << endl;
                    }
                }
            }

            ReadProcessMemory(processHandle, (LPVOID)signalAddress, &signalValue, sizeof(signalValue), NULL);
            battle currentBattle;
            if (signalValue >= 0 && signalValue <= 1)
            {
                currentBattle.battleType = signalValue;
                currentBattle.turnNumber = turnNumber;
                ReadProcessMemory(processHandle, (LPVOID)(battleInfoAddress + 0x18), &currentBattle.pos.x, sizeof(currentBattle.pos.x), NULL);
                ReadProcessMemory(processHandle, (LPVOID)(battleInfoAddress + 0x1C), &currentBattle.pos.y, sizeof(currentBattle.pos.y), NULL);
                ReadProcessMemory(processHandle, (LPVOID)(battleInfoAddress + 0xD0), &currentBattle.attackingArmyCount, sizeof(currentBattle.attackingArmyCount), NULL);
                ReadProcessMemory(processHandle, (LPVOID)(battleInfoAddress + 0x1C2C + 0xD0), &currentBattle.defendingArmyCount, sizeof(currentBattle.defendingArmyCount), NULL);
                ReadProcessMemory(processHandle, (LPVOID)(battleInfoAddress + 0x1CB0), &currentBattle.attackingArmySize, sizeof(currentBattle.attackingArmySize), NULL);
                ReadProcessMemory(processHandle, (LPVOID)(battleInfoAddress + 0x1C2C + 0x1CB0), &currentBattle.defendingArmySize, sizeof(currentBattle.defendingArmySize), NULL);
                for (int i = 0; i < currentBattle.attackingArmyCount; i++)
                {
                    army A;
                    ReadProcessMemory(processHandle, (LPVOID)(battleInfoAddress + 0xF4 + 0x6C * i), &A.armyID, sizeof(A.armyID), NULL);
                    int armySize = 0, unit, unitList, f, character;
                    ReadProcessMemory(processHandle, (LPVOID)(A.armyID + 0x64), &A.unitCount, sizeof(A.unitCount), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(A.armyID + 0x5C), &unitList, sizeof(unitList), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(A.armyID + 0x54), &f, sizeof(f), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(f + 0xA0), &f, sizeof(f), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(A.armyID + 0xF0), &character, sizeof(character), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(character + 0xC), &A.pos.x, sizeof(A.pos.x), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(character + 0x10), &A.pos.y, sizeof(A.pos.y), NULL);
                    A.factionID = f;
                    A.factionName = factionMap[f];
                    for (int j = 0; j < A.unitCount; j++)
                    {
                        struct unit U;
                        ReadProcessMemory(processHandle, (LPVOID)(unitList + j * 4), &unit, sizeof(unit), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(unit + 0x280), &U.startSize, sizeof(U.startSize), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(unit + 0x50), &U.type, sizeof(U.type), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(U.type + 0x8), &U.type, sizeof(U.type), NULL);
                        U.unitName = unitNames[U.type];
                        armySize += U.startSize;
                        fData[f].unitSizeCount[U.type] += U.startSize;
                        fData[f].unitTypeCount[U.type]++;
                        A.units.push_back(U);
                    }
                    A.startingSize = armySize;
                    currentBattle.attackingArmies.push_back(A);
                }
                for (int i = 0; i < currentBattle.defendingArmyCount; i++)
                {
                    army A;
                    ReadProcessMemory(processHandle, (LPVOID)(battleInfoAddress + 0xF4 + 0x6C * i + 0x1C2C), &A.armyID, sizeof(A.armyID), NULL);
                    int armySize = 0, unit, unitList, f, character;
                    ReadProcessMemory(processHandle, (LPVOID)(A.armyID + 0x64), &A.unitCount, sizeof(A.unitCount), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(A.armyID + 0x5C), &unitList, sizeof(unitList), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(A.armyID + 0x54), &f, sizeof(f), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(f + 0xA0), &f, sizeof(f), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(A.armyID + 0xF0), &character, sizeof(character), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(character + 0xC), &A.pos.x, sizeof(A.pos.x), NULL);
                    ReadProcessMemory(processHandle, (LPVOID)(character + 0x10), &A.pos.y, sizeof(A.pos.y), NULL);
                    A.factionID = f;
                    A.factionName = factionMap[f];
                    for (int j = 0; j < A.unitCount; j++)
                    {
                        struct unit U;
                        ReadProcessMemory(processHandle, (LPVOID)(unitList + j * 4), &unit, sizeof(unit), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(unit + 0x280), &U.startSize, sizeof(U.startSize), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(unit + 0x50), &U.type, sizeof(U.type), NULL);
                        ReadProcessMemory(processHandle, (LPVOID)(U.type + 0x8), &U.type, sizeof(U.type), NULL);
                        U.unitName = unitNames[U.type];
                        armySize += U.startSize;
                        fData[f].unitSizeCount[U.type] += U.startSize;
                        fData[f].unitTypeCount[U.type]++;
                        A.units.push_back(U);
                    }
                    A.startingSize = armySize;
                    currentBattle.defendingArmies.push_back(A);
                }

                currentBattle.battleType = field;
                if (calculateDistance(cityCoordinateMap[findClosestCity(currentBattle.defendingArmies[0].pos)], currentBattle.defendingArmies[0].pos) == 0)
                {

                    currentBattle.battleType = siege;
                }

                else if (calculateDistance(cityCoordinateMap[findClosestCity(currentBattle.attackingArmies[0].pos)], currentBattle.attackingArmies[0].pos) == 0)
                {
                    currentBattle.battleType = sally;
                }

                else if (currentBattle.defendingArmies[0].units[0].type >= 245 && currentBattle.defendingArmies[0].units[0].type <= 252)
                {
                    currentBattle.battleType = naval;
                }
                WriteProcessMemory(processHandle, (LPVOID)signalAddress, &defValue, sizeof(defValue), NULL);

                if (signalValue == 1)
                {
                    currentBattle.withdraw = true;
                    fData[currentBattle.defendingArmies[0].factionID].withdraws++;
                    fData[currentBattle.attackingArmies[0].factionID].enemyWithdraws++;
                    battles.push_back(currentBattle);
                    continue;
                }
                else
                {
                    currentBattle.withdraw = false;
                    while (signalValue != 1)
                    {
                        ReadProcessMemory(processHandle, (LPVOID)signalAddress, &signalValue, sizeof(signalValue), NULL);
                    }

                    for (int i = 0; i < currentBattle.attackingArmyCount; i++)
                    {
                        int armySize = 0, unit, unitList;
                        ReadProcessMemory(processHandle, (LPVOID)(currentBattle.attackingArmies[i].armyID + 0x5C), &unitList, sizeof(unitList), NULL);
                        //ReadProcessMemory(processHandle, (LPVOID)(currentBattle.attackingArmies[i].armyID + 0x64), &currentBattle.attackingArmies[i].endUnitCount, sizeof(currentBattle.attackingArmies[i].endUnitCount), NULL);
                        for (int j = 0; j < currentBattle.attackingArmies[i].unitCount; j++)
                        {
                            ReadProcessMemory(processHandle, (LPVOID)(unitList + j * 4), &unit, sizeof(unit), NULL);
                            ReadProcessMemory(processHandle, (LPVOID)(unit + 0x280), &currentBattle.attackingArmies[i].units[j].endSize, sizeof(currentBattle.attackingArmies[i].units[j].endSize), NULL);
                            armySize += currentBattle.attackingArmies[i].units[j].endSize;
                            currentBattle.attackingArmies[i].units[j].losses = currentBattle.attackingArmies[i].units[j].startSize - currentBattle.attackingArmies[i].units[j].endSize;
                        }
                        currentBattle.attackingArmies[i].soldiersLeft = armySize;
                        currentBattle.attackingArmies[i].losses = currentBattle.attackingArmies[i].startingSize - currentBattle.attackingArmies[i].soldiersLeft;
                    }
                    for (int i = 0; i < currentBattle.defendingArmyCount; i++)
                    {
                        int armySize = 0, unit, unitList;
                        ReadProcessMemory(processHandle, (LPVOID)(currentBattle.defendingArmies[i].armyID + 0x5C), &unitList, sizeof(unitList), NULL);
                        //ReadProcessMemory(processHandle, (LPVOID)(currentBattle.defendingArmies[i].armyID + 0x64), &currentBattle.defendingArmies[i].endUnitCount, sizeof(currentBattle.defendingArmies[i].endUnitCount), NULL);
                        for (int j = 0; j < currentBattle.defendingArmies[i].unitCount; j++)
                        {
                            ReadProcessMemory(processHandle, (LPVOID)(unitList + j * 4), &unit, sizeof(unit), NULL);
                            ReadProcessMemory(processHandle, (LPVOID)(unit + 0x280), &currentBattle.defendingArmies[i].units[j].endSize, sizeof(currentBattle.defendingArmies[i].units[j].endSize), NULL);
                            armySize += currentBattle.defendingArmies[i].units[j].endSize;
                            currentBattle.defendingArmies[i].units[j].losses = currentBattle.defendingArmies[i].units[j].startSize - currentBattle.defendingArmies[i].units[j].endSize;
                        }
                        currentBattle.defendingArmies[i].soldiersLeft = armySize;
                        currentBattle.defendingArmies[i].losses = currentBattle.defendingArmies[i].startingSize - currentBattle.defendingArmies[i].soldiersLeft;
                    }

                    int win_loss_status;
                    ReadProcessMemory(processHandle, (LPVOID)(battleInfoAddress + 0x98 + 0x24), &win_loss_status, sizeof(win_loss_status), NULL);
                    if (win_loss_status == 0) //defender won
                    {
                        currentBattle.winner = currentBattle.defendingArmies[0].factionID;
                        currentBattle.loser = currentBattle.attackingArmies[0].factionID;
                        if (currentBattle.battleType != naval)
                        {
                            if (currentBattle.battleType == siege)
                            {
                                fData[currentBattle.winner].siegeDefenses++;
                                fData[currentBattle.winner].siegeDefenseWins++;
                                fData[currentBattle.loser].siegeAttacks++;
                                fData[currentBattle.winner].eData[currentBattle.loser].siegeDefenses++;
                                fData[currentBattle.winner].eData[currentBattle.loser].siegeDefenseWins++;
                                fData[currentBattle.loser].eData[currentBattle.winner].siegeAttacks++;
                            }
                            fData[currentBattle.winner].defends++;
                            fData[currentBattle.loser].attacks++;
                            fData[currentBattle.winner].eData[currentBattle.loser].defends++;
                            fData[currentBattle.loser].eData[currentBattle.winner].attacks++;
                            if (currentBattle.attackingArmySize > (currentBattle.defendingArmySize * 1.25))
                            {
                                fData[currentBattle.winner].numbersDisadvantage++;
                                fData[currentBattle.winner].numbersDisadvantageWin++;
                                fData[currentBattle.loser].numbersAdvantage++;
                                fData[currentBattle.winner].eData[currentBattle.loser].numbersDisadvantage++;
                                fData[currentBattle.winner].eData[currentBattle.loser].numbersDisadvantageWin++;
                                fData[currentBattle.loser].eData[currentBattle.winner].numbersAdvantage++;
                            }
                            else if (currentBattle.defendingArmySize > (currentBattle.attackingArmySize * 1.25))
                            {
                                fData[currentBattle.winner].numbersAdvantage++;
                                fData[currentBattle.winner].numbersAdvantageWin++;
                                fData[currentBattle.loser].numbersDisadvantage++;
                                fData[currentBattle.winner].eData[currentBattle.loser].numbersAdvantage++;
                                fData[currentBattle.winner].eData[currentBattle.loser].numbersAdvantageWin++;
                                fData[currentBattle.loser].eData[currentBattle.winner].numbersDisadvantage++;
                            }
                            else
                            {
                                 fData[currentBattle.winner].numbersEqual++;
                                fData[currentBattle.winner].numbersEqualWin++;
                                fData[currentBattle.loser].numbersEqual++;
                                fData[currentBattle.winner].eData[currentBattle.loser].numbersEqual++;
                                fData[currentBattle.winner].eData[currentBattle.loser].numbersEqualWin++;
                                fData[currentBattle.loser].eData[currentBattle.winner].numbersEqual++;
                            }
                        }
                    }
                    else if (win_loss_status == 1) //draw
                    {
                        currentBattle.winner = 50;
                        currentBattle.loser = 50;
                        fData[currentBattle.defendingArmies[0].factionID].battles++;
                        fData[currentBattle.attackingArmies[0].factionID].battles++;
                        fData[currentBattle.defendingArmies[0].factionID].eData[currentBattle.defendingArmies[0].factionID].battles++;
                        fData[currentBattle.attackingArmies[0].factionID].eData[currentBattle.attackingArmies[0].factionID].battles++;
                        fData[currentBattle.defendingArmies[0].factionID].drawCount++;
                        fData[currentBattle.attackingArmies[0].factionID].drawCount++;
                        if (currentBattle.battleType == naval) //is this even possible?
                        {
                            fData[currentBattle.attackingArmies[0].factionID].navalBattles++;
                            fData[currentBattle.defendingArmies[0].factionID].navalBattles++;
                        }
                        else
                        {
                            if (currentBattle.battleType == siege)
                            {
                                fData[currentBattle.defendingArmies[0].factionID].siegeDefenses++;
                                fData[currentBattle.attackingArmies[0].factionID].siegeAttacks++;
                                fData[currentBattle.defendingArmies[0].factionID].eData[currentBattle.defendingArmies[0].factionID].siegeDefenses++;
                                fData[currentBattle.attackingArmies[0].factionID].eData[currentBattle.attackingArmies[0].factionID].siegeAttacks++;
                            }
                            fData[currentBattle.attackingArmies[0].factionID].landBattles++;
                            fData[currentBattle.defendingArmies[0].factionID].landBattles++;
                            fData[currentBattle.defendingArmies[0].factionID].eData[currentBattle.defendingArmies[0].factionID].landBattles++;
                            fData[currentBattle.attackingArmies[0].factionID].eData[currentBattle.attackingArmies[0].factionID].landBattles++;
                        }
                        fData[currentBattle.defendingArmies[0].factionID].draws.push_back(currentBattle);
                        fData[currentBattle.attackingArmies[0].factionID].draws.push_back(currentBattle);
                    }
                    else if (win_loss_status == 2) //attacker won
                    {
                        currentBattle.winner = currentBattle.attackingArmies[0].factionID;
                        currentBattle.loser = currentBattle.defendingArmies[0].factionID;
                        if (currentBattle.battleType != naval)
                        {
                            if (currentBattle.battleType == siege)
                            {
                                fData[currentBattle.loser].siegeDefenses++;
                                fData[currentBattle.winner].siegeAttacks++;
                                fData[currentBattle.winner].siegeAttackWins++;
                                fData[currentBattle.winner].eData[currentBattle.loser].siegeDefenses++;
                                fData[currentBattle.winner].eData[currentBattle.loser].siegeAttackWins++;
                                fData[currentBattle.loser].eData[currentBattle.winner].siegeAttacks++;
                            }
                            fData[currentBattle.winner].attacks++;
                            fData[currentBattle.loser].defends++;
                            fData[currentBattle.winner].eData[currentBattle.loser].defends++;
                            fData[currentBattle.loser].eData[currentBattle.winner].attacks++;
                            if (currentBattle.attackingArmySize < (currentBattle.defendingArmySize * 1.25))
                            {
                                fData[currentBattle.winner].numbersDisadvantage++;
                                fData[currentBattle.winner].numbersDisadvantageWin++;
                                fData[currentBattle.loser].numbersAdvantage++;
                                fData[currentBattle.winner].eData[currentBattle.loser].numbersDisadvantage++;
                                fData[currentBattle.winner].eData[currentBattle.loser].numbersDisadvantageWin++;
                                fData[currentBattle.loser].eData[currentBattle.winner].numbersAdvantage++;
                            }
                            else if (currentBattle.defendingArmySize < (currentBattle.attackingArmySize * 1.25))
                            {
                                fData[currentBattle.winner].numbersAdvantage++;
                                fData[currentBattle.winner].numbersAdvantageWin++;
                                fData[currentBattle.loser].numbersDisadvantage++;
                                fData[currentBattle.winner].eData[currentBattle.loser].numbersAdvantage++;
                                fData[currentBattle.winner].eData[currentBattle.loser].numbersAdvantageWin++;
                                fData[currentBattle.loser].eData[currentBattle.winner].numbersDisadvantage++;
                            }
                            else
                            {
                                fData[currentBattle.winner].numbersEqual++;
                                fData[currentBattle.winner].numbersEqualWin++;
                                fData[currentBattle.loser].numbersEqual++;
                                fData[currentBattle.winner].eData[currentBattle.loser].numbersEqual++;
                                fData[currentBattle.winner].eData[currentBattle.loser].numbersEqualWin++;
                                fData[currentBattle.loser].eData[currentBattle.winner].numbersEqual++;
                            }
                        }

                        if (currentBattle.battleType == siege)
                        {
                            fData[currentBattle.winner].settlementsCaptured++;
                            fData[currentBattle.loser].settlementsLost++;
                            fData[currentBattle.winner].eData[currentBattle.loser].settlementsCaptured++;
                            fData[currentBattle.loser].eData[currentBattle.winner].settlementsLost++;
                        }
                    }
                    if (currentBattle.winner != 50)
                    {
                        fData[currentBattle.winner].battles++;
                        fData[currentBattle.loser].battles++;
                        fData[currentBattle.winner].wins++;
                        fData[currentBattle.loser].losses++;
                        fData[currentBattle.winner].eData[currentBattle.loser].battles++;
                        fData[currentBattle.winner].eData[currentBattle.loser].wins++;
                        fData[currentBattle.loser].eData[currentBattle.winner].battles++;
                        fData[currentBattle.loser].eData[currentBattle.winner].losses++;
                        if (currentBattle.battleType == naval)
                        {
                            fData[currentBattle.winner].navalBattles++;
                            fData[currentBattle.loser].navalBattles++;
                            fData[currentBattle.winner].navalWins++;
                            fData[currentBattle.loser].navalLosses++;
                            fData[currentBattle.winner].eData[currentBattle.loser].navalBattles++;
                            fData[currentBattle.winner].eData[currentBattle.loser].navalWins++;
                            fData[currentBattle.loser].eData[currentBattle.winner].navalBattles++;
                            fData[currentBattle.loser].eData[currentBattle.winner].navalLosses++;
                        }
                        else
                        {
                            fData[currentBattle.winner].landBattles++;
                            fData[currentBattle.loser].landBattles++;
                            fData[currentBattle.winner].landWins++;
                            fData[currentBattle.loser].landLosses++;
                            fData[currentBattle.winner].eData[currentBattle.loser].landBattles++;
                            fData[currentBattle.winner].eData[currentBattle.loser].landWins++;
                            fData[currentBattle.loser].eData[currentBattle.winner].landBattles++;
                            fData[currentBattle.loser].eData[currentBattle.winner].landLosses++;
                        }
                        fData[currentBattle.winner].battlesWon.push_back(currentBattle);
                        fData[currentBattle.loser].battlesLost.push_back(currentBattle);
                    }

                    battles.push_back(currentBattle);
                    if (currentBattle.battleType == field && currentBattle.withdraw == false)
                    {
                        battleDat << currentBattle.winner << " ";
                        battleDat << currentBattle.loser << " ";
                        battleDat << currentBattle.pos.x << " ";
                        battleDat << currentBattle.pos.y << " ";
                        battleDat << turnNumber << endl;
                    }
                    int attackArmySize = 0, defendArmySize = 0;
                    for (int i = 0; i < currentBattle.attackingArmyCount; i++)
                    {
                        attackArmySize += currentBattle.attackingArmies[i].startingSize;
                    }

                    for (int i = 0; i < currentBattle.defendingArmyCount; i++)
                    {
                        defendArmySize += currentBattle.defendingArmies[i].startingSize;
                    }
                    battleData << "{" << currentBattle.attackingArmyCount << ", " << attackArmySize << ", " << currentBattle.defendingArmyCount << ", " << defendArmySize << ", " << currentBattle.winner << ", " << currentBattle.loser << ", " << currentBattle.battleType << ", " << currentBattle.withdraw << ", " << currentBattle.pos.x << ", " << currentBattle.pos.y << "}" << endl;
                    battleData << "{";
                    for (int i = 0; i < currentBattle.attackingArmyCount; i++)
                    {
                        army A = currentBattle.attackingArmies[i];
                        battleData << "{" << A.factionID << ", " << A.startingSize << ", " << A.losses << ", " << A.unitCount << ", " << A.pos.x << ", " << A.pos.y << "}" << endl;
                        for (int j = 0; j < A.unitCount; j++)
                        {
                            unit U = A.units[j];
                            battleData << ", {" << U.startSize << ", " << U.type << ", " << U.losses << ", " << U.unitName << "}";
                        }
                    }
                    battleData << "}" << endl;

                    battleData << "{";
                    for (int i = 0; i < currentBattle.defendingArmyCount; i++)
                    {
                        army A = currentBattle.defendingArmies[i];
                        battleData << "{" << A.factionID << ", " << A.startingSize << ", " << A.losses << ", " << A.unitCount << ", " << A.pos.x << ", " << A.pos.y << "}" << endl;
                        for (int j = 0; j < A.unitCount; j++)
                        {
                            unit U = A.units[j];
                            battleData << ", {" << U.startSize << ", " << U.type << ", " << U.losses << ", " << U.unitName << "}";
                        }
                    }
                    battleData << "}" << endl;
                    WriteProcessMemory(processHandle, (LPVOID)signalAddress, &defValue, sizeof(defValue), NULL);
                }
            }
        }
        printStatistics(fData, battleData);

        TerminateProcess(processHandle, 1);
        campaigns++;
    }
