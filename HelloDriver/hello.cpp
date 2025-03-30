#include <ntddk.h>
//驱动卸载
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("The driver is unloaded\n"));
}

//驱动入口
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);
	//卸载函数
	DriverObject->DriverUnload = DriverUnload;
	KdPrint(("hello driver"));
	
	return STATUS_SUCCESS;

}
