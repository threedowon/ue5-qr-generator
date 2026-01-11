#include "QRGeneratorFunctionLibrary.h"
#include "Engine/Texture2D.h"
#include "zxing/QRWriter.h"
#include "zxing/BitMatrix.h"

UTexture2D* UQRGeneratorFunctionLibrary::GenerateQRCode(
    const FString& Url,
    int32 Size,
    FColor ForegroundColor,      // QR 픽셀(검정 부분) 색
    FColor BackgroundColor       // QR 빈 공간(흰색 부분) 색
)
{
    using namespace ZXing;
    using namespace ZXing::QRCode;

    Writer QRWriter;
    auto Matrix = QRWriter.encode(TCHAR_TO_UTF8(*Url), Size, Size);

    TArray<FColor> Pixels;
    Pixels.SetNum(Size * Size);

    for (int y = 0; y < Size; y++)
    {
        for (int x = 0; x < Size; x++)
        {
            bool bBlack = Matrix.get(x, y);
            Pixels[y * Size + x] = bBlack ? ForegroundColor : BackgroundColor;
        }
    }

    UTexture2D* Texture = UTexture2D::CreateTransient(Size, Size, PF_B8G8R8A8);
    void* Data = Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
    FMemory::Memcpy(Data, Pixels.GetData(), Pixels.Num() * sizeof(FColor));
    Texture->GetPlatformData()->Mips[0].BulkData.Unlock();
    Texture->UpdateResource();

    return Texture;
}