#include <ntddk.h>
//����ж��
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("The driver is unloaded\n"));
}

//�������
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);
	//ж�غ���
	DriverObject->DriverUnload = DriverUnload;
	KdPrint(("hello driver"));
	
	return STATUS_SUCCESS;

}
