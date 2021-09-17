#pragma once

class OWindow
{
public:
	OWindow();
	~OWindow();

	void onDestroy();
	bool isClosed();
private:
	void* m_handle = nullptr;
};

