#ifndef LIBME_TEST_STRING
  #define LIBME_TEST_STRING(f, v, r)
#endif
LIBME_TEST_STRING(replace(3, 5, "no"), "Hi everybody!", "Hi nobody!");
LIBME_TEST_STRING(replace(14, 5, "Smithers"), "My name is Mr Burns!", "My name is Mr Smithers!");
LIBME_TEST_STRING(insert(3, "name"), "My  is Mr Burns!", "My name is Mr Burns!");
LIBME_TEST_STRING(insert(20, " :)"), "My name is Mr Burns!", "My name is Mr Burns! :)");
LIBME_TEST_STRING(erase(3, 5), "My name is Mr Burns!", "My is Mr Burns!");
LIBME_TEST_STRING(erase(str.begin() + 18), "My name is Mr Burns!", "My name is Mr Burn!");
LIBME_TEST_STRING(erase(str.begin() + 3, str.begin() + 7), "My name is Mr Burns!", "My  is Mr Burns!");
LIBME_TEST_STRING(push_back('!'), "My name is Mr Burns", "My name is Mr Burns!");
LIBME_TEST_STRING(append('!', 3), "My name is Mr Burns", "My name is Mr Burns!!!");
LIBME_TEST_STRING(append("water"), "I like ", "I like water");
LIBME_TEST_STRING(assign('#'), "Hello", "#");
LIBME_TEST_STRING(assign("A text"), "Hello everyone", "A text");
LIBME_TEST_STRING(clear(), "Hello everyone!", "");
LIBME_TEST_STRING(pop_back(), "Hello everyone!", "Hello everyone");
LIBME_TEST_STRING(resize(18, '#'), "I'm Batman!", "I'm Batman!#######");
LIBME_TEST_STRING(c_str(), "Woohoo!", "Woohoo!");
