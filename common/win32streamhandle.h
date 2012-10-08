// taken form http://yusuke.rurinet.ne.jp/wiki/wiki.cgi?page=STL+streambuf

#ifndef __WIN32_STREAM_HANDLE_HEADER__INCLUDED__
#define __WIN32_STREAM_HANDLE_HEADER__INCLUDED__

#include <windows.h>

#include <iostream>
#include <vector>
#include <stdexcept>

namespace win32 {

class Win32Exception : public std::runtime_error {
public:
	DWORD errorCode;
public:
	Win32Exception(DWORD errorCode_)
		: std::runtime_error("Win32Exception"), errorCode(errorCode_)
	{
	}
};

template <class Ch,class Tr=std::char_traits<Ch> >
class basic_win32handle_streambuf : public std::basic_streambuf<Ch,Tr> {
public:
	explicit basic_win32handle_streambuf(HANDLE h) : handle(h), bufferSize(1024) { init(); }
	basic_win32handle_streambuf(HANDLE h, int buffer) : handle(h), bufferSize(buffer) { init(); }
	virtual ~basic_win32handle_streambuf();

protected:
	const int bufferSize;
	void init();
	HANDLE handle;

};

template <class Ch,class Tr=std::char_traits<Ch> >
class basic_win32handle_ostreambuf : public basic_win32handle_streambuf<Ch,Tr> {
public:
	explicit basic_win32handle_ostreambuf(HANDLE h) : basic_win32handle_streambuf<Ch,Tr>(h) { init(); }
	basic_win32handle_ostreambuf(HANDLE h, int buffer) : basic_win32handle_streambuf<Ch,Tr>(h, buffer) { init(); }
	virtual ~basic_win32handle_ostreambuf();

protected:
	virtual int_type overflow(int_type c=Tr::eof())
	{
		// �o�b�t�@�����ӂꂽ�̂ŏ������݂��s��
		write();

		// ���͂����܂�炵���B�悭�m��Ȃ���
		if(c!=Tr::eof()){
			// �󂯎�����������o�b�t�@�ɑ}��
			*pptr()=Tr::to_char_type(c);
			// �o�b�t�@�̏������݈ʒu���C���N�������g
			pbump(1);
			return Tr::not_eof(c);

		} else {
			return Tr::eof();
		}
	}

	virtual int_type sync()
	{
		flush();
		return 0;
	}

private:
	Ch* writeBuffer;
	void write();
	void flush();
	void init();

};


template <class Ch,class Tr=std::char_traits<Ch> >
class basic_win32handle_istreambuf : public basic_win32handle_streambuf<Ch,Tr> {
public:
	explicit basic_win32handle_istreambuf(HANDLE h) : basic_win32handle_streambuf<Ch,Tr>(h) { init(); }
	basic_win32handle_istreambuf(HANDLE h, int buffer) : basic_win32handle_streambuf<Ch,Tr>(h, buffer) { init(); }

	virtual ~basic_win32handle_istreambuf();

protected:
	virtual int_type underflow(void)
	{
		if(egptr()<=gptr()){
			// �o�b�t�@���g���ʂ������̂œǂݍ��݂��s��
			read();

			if(egptr()<=gptr()){
				// ����1�o�C�g���ǂ߂Ȃ�����
				return Tr::eof();
			}
		}

		// �ǂ߂��̂ōŏ��̈��Ԃ�
		return Tr::to_int_type(*gptr());
	}


private:
	Ch* readBuffer;
	void read();
	void init();

};



/**
 * Win32 HANDLE �� iostream
 */
template <class Ch,class Tr=std::char_traits<Ch> >
class basic_win32handle_istream : public std::basic_istream<Ch,Tr> {
public:
	/**
	 * HANDLE ���� iostream ���\�z����
	 */
	basic_win32handle_istream(HANDLE h)
		: std::basic_istream<Ch,Tr>(new basic_win32handle_istreambuf<Ch,Tr>(h))
	{
	}

	~basic_win32handle_istream(void)
	{
		delete rdbuf();
	}

private:

};

/**
 * Win32 HANDLE �� iostream
 */
template <class Ch,class Tr=std::char_traits<Ch> >
class basic_win32handle_ostream : public std::basic_ostream<Ch,Tr> {
public:
	/**
	 * HANDLE ���� iostream ���\�z����
	 */
	basic_win32handle_ostream(HANDLE h)
		: std::basic_ostream<Ch,Tr>(new basic_win32handle_ostreambuf<Ch,Tr>(h))
	{
	}

	~basic_win32handle_ostream(void)
	{
		delete rdbuf();
	}

private:

};


template <class Ch,class Tr>
inline
void basic_win32handle_ostreambuf<Ch, Tr>::init()
{
	writeBuffer = new Ch[bufferSize];

	// �������݃|�C���^�̐ݒ�
	// �o�b�t�@�I�[�܂ł�����悤��
	setp( writeBuffer, writeBuffer + bufferSize );

}

template <class Ch,class Tr>
inline
void basic_win32handle_istreambuf<Ch, Tr>::init()
{
	readBuffer  = new Ch[bufferSize];

	// �ǂݎ��|�C���^�̐ݒ�
	// �ŏ��͉����ǂݍ���ł��Ȃ����
	setg( readBuffer, readBuffer + bufferSize, readBuffer + bufferSize );
}

/**
 * basic_win32handle_streambuf�̏��������s��
 */
template <class Ch,class Tr>
inline
void basic_win32handle_streambuf<Ch, Tr>::init()
{
}

template <class Ch,class Tr>
inline
basic_win32handle_ostreambuf<Ch, Tr>::~basic_win32handle_ostreambuf()
{
	flush();
	delete [] writeBuffer;

}

template <class Ch,class Tr>
inline
basic_win32handle_istreambuf<Ch, Tr>::~basic_win32handle_istreambuf()
{
	delete [] readBuffer;
}

template <class Ch,class Tr>
inline
basic_win32handle_streambuf<Ch, Tr>::~basic_win32handle_streambuf()
{
}

/**
 * ���ۂɃn���h�����g���ăo�b�t�@�������o��
 */
template <class Ch,class Tr>
inline
void basic_win32handle_ostreambuf<Ch, Tr>::write()
{
	DWORD ws = (pptr() - pbase()) * sizeof(Ch);
	DWORD written;

	BOOL rc = WriteFile(handle, pbase(), ws, &written, NULL);
	if (FALSE == rc)
		throw Win32Exception(::GetLastError());

	setp(pbase(), epptr());
}

/**
 * ���ۂɃn���h�����g���ăo�b�t�@�ɓǂݍ���
 */
template <class Ch,class Tr>
inline
void basic_win32handle_istreambuf<Ch, Tr>::read()
{
	DWORD rs = bufferSize * sizeof(Ch);
	DWORD readed;

	BOOL rc = ReadFile(handle, readBuffer, rs, &readed, NULL);
	if (FALSE == rc)
		throw Win32Exception(::GetLastError());

	setg(readBuffer, readBuffer, readBuffer + readed);
}

/**
 * �o�b�t�@���t���b�V������
 */
template <class Ch,class Tr>
inline
void basic_win32handle_ostreambuf<Ch, Tr>::flush()
{
	// flush ����
	write();
}

}; // namespace win32


#endif //__WIN32_STREAM_HANDLE_HEADER__INCLUDED__

