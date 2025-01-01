param (
    [string]$folderName
)

# 检查文件夹名称是否提供
if (-not $folderName) {
    Write-Host "错误: 请提供文件夹名称。" -ForegroundColor Red
    exit
}

# 获取当前脚本所在路径
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path

# 固定资源文件夹路径
$resourceDir = Join-Path -Path $scriptDir -ChildPath "example_template"

# 检查资源文件夹是否存在
if (-not (Test-Path $resourceDir)) {
    Write-Host "错误: 资源文件夹 'resources' 不存在。" -ForegroundColor Red
    exit
}

# 定义资源文件路径
$sourceCMakeLists = Join-Path -Path $resourceDir -ChildPath "CMakeLists_CommonTemplate.txt"
$sourceImage = Join-Path -Path $resourceDir -ChildPath "image.jpg"

# 检查源文件路径是否存在
if (-not (Test-Path $sourceCMakeLists)) {
    Write-Host "错误: CMakeLists.Tmp.in 文件不存在。" -ForegroundColor Red
    exit
}

if (-not (Test-Path $sourceImage)) {
    Write-Host "错误: image.png 文件不存在。" -ForegroundColor Red
    exit
}

# 1. 创建目标文件夹
New-Item -Path $folderName -ItemType Directory -Force

# 2. 复制并重命名CMakeLists.Tmp.in文件为CMakeLists.txt
$destinationCMake = Join-Path -Path $folderName -ChildPath "CMakeLists.txt"
Copy-Item -Path $sourceCMakeLists -Destination $destinationCMake

# 3. 创建.cpp文件
$cppFile = Join-Path -Path $folderName -ChildPath "$folderName.cpp"
New-Item -Path $cppFile -ItemType File -Force

# 4. 复制image.png文件
$destinationImage = Join-Path -Path $folderName -ChildPath "image.jpg"
Copy-Item -Path $sourceImage -Destination $destinationImage

Write-Host "文件夹 '$folderName' 创建完成，文件已复制。" -ForegroundColor Green
