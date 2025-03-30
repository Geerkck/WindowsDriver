#include <ntddk.h>
//����ж�غ���
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	PDEVICE_OBJECT DeviceObject = DriverObject->DeviceObject;

	//�����豸��������ɾ��
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
	
	//��ʼ���豸����
	RtlInitUnicodeString(&DeviceName, L"\\Device\\MyDevice");
	//��ʼ����������
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
		KdPrint(("����ʧ��,������:0x%X\n", status));
	}
	//������������
	status = IoCreateSymbolicLink(&SymbolicLinkName, &DeviceName);
	
	if (!NT_SUCCESS(status))
	{
		KdPrint(("����ʧ��,������:0x%X\n", status));
		IoDeleteDevice(DeviceObject);
		return status;
	}

	//��������ж�غ���
	DriverObject->DriverUnload = DriverUnload;
	KdPrint(("����ж��"));
	return STATUS_SUCCESS;
	
}