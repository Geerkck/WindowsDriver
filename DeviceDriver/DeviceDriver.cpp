#include <ntddk.h>
//驱动卸载函数
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	PDEVICE_OBJECT DeviceObject = DriverObject->DeviceObject;

	//遍历设备对象链表并删除
	while (DeviceObject)
	{
		PDEVICE_OBJECT NextDevice = DeviceObject->NextDevice;
		IoDeleteDevice(DeviceObject);
		DeviceObject = NextDevice;
	}
	KdPrint(("Device driver unload\n"));
}
VOID DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegisterPath)
{
	UNREFERENCED_PARAMETER(RegisterPath);
	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_OBJECT DeviceObject = NULL;
	UNICODE_STRING DeviceName;
	UNICODE_STRING SymbolicLinkName;
	
	//初始化设备名称
	RtlInitUnicodeString(&DeviceName, L"\\Device\\MyDevice");
	//初始化符号链接
	RtlInitUnicodeString(&DeviceName, L"\\??\\MyDevice");

	status = IoCreateDevice(
		DriverObject,
		0,
		&DeviceName,
		FILE_DEVICE_UNKNOWN,
		0,
		false,
		&DeviceObject
	);

	if (!NT_SUCCESS(status))
	{
		KdPrint(("创建失败,错误码:0x%X\n", status));
	}
	//创建符号链接
	status = IoCreateSymbolicLink(&SymbolicLinkName, &DeviceName);
	
	if (!NT_SUCCESS(status))
	{
		KdPrint(("创建失败,错误码:0x%X\n", status));
		IoDeleteDevice(DeviceObject);
		return status;
	}

	//设置驱动卸载函数
	DriverObject->DriverUnload = DriverUnload;
	KdPrint(("驱动卸载"));
	return STATUS_SUCCESS;
	
}