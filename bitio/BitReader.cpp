/*
 * BitReader.cpp
 *
 *  Created on: Mar 17, 2017
 *      Author: dbondin
 */

#include "BitReader.h"

namespace bitio {

BitReader::BitReader() {
	this->is = NULL;
	this->current_bit = 8;
	this->current_byte = 0;
}

BitReader::~BitReader() {

}

void
BitReader::attach(std::istream * is) {
	this->is = is;
	this->current_bit = 7;
	this->current_byte = 0;
}

std::istream *
BitReader::get_stream() const {
	return this->is;
}

void
BitReader::detach() {
	this->is = NULL;
	this->current_bit = 7;
	this->current_byte = 0;
}

int
BitReader::read_next_bit() {
	if(this->is == NULL) {
		throw new std::exception();
	}

	current_bit ++;

	if(current_bit > 7) {
		(*is)>>current_byte;
		if(is->eof()) {
			throw new std::exception();
		}
		current_bit = 0;
	}

	return (current_byte & (0x80 /* 0b1000000 */ >> current_bit)) ? 1 : 0;
}

} /* namespace a */
