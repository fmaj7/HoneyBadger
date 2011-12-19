// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� LIBRSYNCDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// LIBRSYNCDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef LIBRSYNCDLL_EXPORTS
#define LIBRSYNCDLL_API __declspec(dllexport)
#else
#define LIBRSYNCDLL_API __declspec(dllimport)
#endif

// �����Ǵ� LibRsyncDll.dll ������
class LIBRSYNCDLL_API CLibRsyncDll {
public:
	CLibRsyncDll(void);
	// TODO: �ڴ�������ķ�����
};

extern LIBRSYNCDLL_API int nLibRsyncDll;

LIBRSYNCDLL_API int fnLibRsyncDll(void);

LIBRSYNCDLL_API bool rsync_sig(char* oldfile,char* sigfile);

LIBRSYNCDLL_API bool rsync_delta(char* newfile,char* sigfile,char* deltafile);

LIBRSYNCDLL_API bool rsync_patch(char* oldfile,char* newfile,char* deltafile);
