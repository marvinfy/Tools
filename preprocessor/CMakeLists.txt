
SET(PREPROCESSOR_INC
	preprocessor.h
	)

SET(PREPROCESSOR_SRC
	main.cpp
	preprocessor.cpp
	)

ADD_EXECUTABLE(preprocessor ${PREPROCESSOR_INC} ${PREPROCESSOR_SRC})
