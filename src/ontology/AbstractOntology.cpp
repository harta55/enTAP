/*
 *
 * Developed by Alexander Hart
 * Plant Computational Genomics Lab
 * University of Connecticut
 *
 * For information, contact Alexander Hart at:
 *     entap.dev@gmail.com
 *
 * Copyright 2017, Alexander Hart, Dr. Jill Wegrzyn
 *
 * This file is part of EnTAP.
 *
 * EnTAP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EnTAP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EnTAP.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <boost/serialization/map.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "../EntapGlobals.h"
#include "AbstractOntology.h"
#include "../ExceptionHandler.h"


std::map<std::string,std::vector<std::string>> AbstractOntology::parse_go_list
        (std::string list, std::map<std::string,struct_go_term> &GO_DATABASE,char delim) {

    std::map<std::string,std::vector<std::string>> output;
    std::string temp;
    std::vector<std::vector<std::string>>results;

    if (list.empty()) return output;
    std::istringstream ss(list);
    while (std::getline(ss,temp,delim)) {
        struct_go_term term_info = GO_DATABASE[temp];
        output[term_info.category].push_back(temp + "-" + term_info.term +
                                             "(L=" + term_info.level + ")");
    }
    return output;
}



std::map<std::string,struct_go_term> AbstractOntology::read_go_map () {
    std::map<std::string,struct_go_term> new_map;
    try {
        {
            std::ifstream ifs(GO_DB_PATH);
            boost::archive::binary_iarchive ia(ifs);
            ia >> new_map;
        }
    } catch (std::exception &exception) {
        throw ExceptionHandler(exception.what(), ENTAP_ERR::E_GO_READ);
    }
    return new_map;
};
