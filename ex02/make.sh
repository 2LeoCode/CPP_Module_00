#!/bin/bash

./clean.sh

wget https://projects.intra.42.fr/uploads/document/document/2160/Account.class.hpp
wget https://projects.intra.42.fr/uploads/document/document/2162/tests.cpp

awk 'NR==48{print "\tmutable std::uint32_t\t_checkAmountCount;"}41' Account.class.hpp\
| awk 'NR==33{print "\tinline void\tshowCheckAmountCount(void)\n\t{\n\t\tstd::cout << \"[\" << _accountIndex << \"] Number of times checkAmount() has been called: \" << _checkAmountCount << std::endl;\n\t}"}171'\
| awk 'NR==13{print "# include <iostream>"}20' >> tmp.txt
rm -f Account.class.hpp
cat tmp.txt >> Account.class.hpp
rm -f tmp.txt
awk 'NR==62{print "\taccounts[2].makeWithdrawal(200);\n\taccounts[4].makeWithdrawal(200);\n\taccounts[4].makeWithdrawal(200);\n\taccounts[5].makeWithdrawal(200);\n\taccounts[7].makeWithdrawal(200);\n\tfor(int i = 0; i < 8; i++)\n\t\taccounts[i].showCheckAmountCount();"}135' tests.cpp >> tmp.txt
rm -f tests.cpp
cat tmp.txt >> tests.cpp
rm -f tmp.txt

clang++ -Wall -Werror -Wextra tests.cpp Account.class.cpp -o Account
