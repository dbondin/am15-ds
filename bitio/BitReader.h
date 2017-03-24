/*
 * BitReader.h
 *
 *  Created on: Mar 17, 2017
 *      Author: dbondin
 */

#ifndef BITREADER_H_
#define BITREADER_H_

#include <istream>

namespace bitio {

class BitReader {
public:
	BitReader();
	virtual ~BitReader();
	void attach(std::istream * is);
	std::istream * get_stream() const;
	void detach();
	int read_next_bit();
private:
	std::istream * is;
	unsigned char current_byte;
	int current_bit;
};

} /* namespace a */

#endif /* BITREADER_H_ */
