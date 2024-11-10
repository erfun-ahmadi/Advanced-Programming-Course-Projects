#ifndef CONST_H
#define CONST_H

#include <string>

const int DEADLINE_AFTER_BORROW = 10;
const int DOCUMENT_CEILING_FOR_PROFESSOR = 5;
const int DOCUMENT_CEILING_FOR_STUDENT = 2;
const int EXTEND_CEILING = 2;
const int MAGAZINE_PUBLISH_YEAR = 1390;
const int MAGAZINE_PENALTY_BEFORE_1390 = 2000;
const int MAGAZINE_PENALTY_AFTER_1390 = 3000;
const int REFERENCE_LOW_DAYS_PASSED = 3;
const int REFERENCE_LOW_DAYS_PENALTY = 5000;
const int REFERENCE_MUCH_DAYS_PENALTY = 7000;
const int BOOK_LOW_DAYS_PASSED = 7;
const int BOOK_MEDIUM_DAYS_PASSED = 21;
const int BOOK_LOW_DAYS_PENALTY = 2000;
const int BOOK_MEDIUM_DAYS_PENALTY = 3000;
const int BOOK_MUCH_DAYS_PENALTY = 5000;
const std::string SAME_NAME_ERROR = "Name already exists";
const std::string EMPTY_FIELD_ERROR = "Empty field";
const std::string SAME_DOCUMENT_TITLE = "A document with the specified name already exists";
const std::string INVALID_YEAR = "Invalid year";
const std::string INVALID_NUMBER = "Invalid number";
const std::string INVALID_DAY = "Invalid day";
const std::string BORROW_BORROWED_DOCUMENT = "You borrowed this document already";
const std::string MAX_BORROWED_DOCUMENTS_ERROR = "Maximum number of allowed borrows exceeded";
const std::string NO_EXISTING_DOCUMENT = "This document does not exist";
const std::string MAGAZINE_EXTEND_WARNING = "You can’t renew magazines";
const std::string NO_BORROWED_DOCUMENT = "You have not borrowed this document";
const std::string EXTEND_ON_BORROW_DAY = "You can’t extend and borrow a document on the same day";
const std::string EXTEND_AFTER_DEADLINE = "You can’t renew a document after receiving a penalty";
const std::string NO_MORE_EXTENDS = "You can’t renew a document more than two times";

#endif