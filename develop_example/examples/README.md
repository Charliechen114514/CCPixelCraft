# Example Directory

​	This is a directory contains opencv example, for developers better understanding the usage of opencv. To make a start, make sure the top level CMakeLists.txt enables the build of example(Note: set the REQ_EXAMPLE as ON to enable the build)

​	one could start from 0.beginners exampe and then touring the folders he or she interested in.

​	For maintainers, one can use create_example.ps1 by following a name of the demo folder

​	For example, in powershell, depatch the work as

```
./create_example.ps1 demo
```

​	To create a fast creation of demo example.

​	To let the demo engaged in the build section, remember to add the demo_folder name into the  EXAMPLES_LISTS in develop_example/examples/CMakeLists.txt, this is using in controlling which demos participated in the building sections. 

​	此目录包含 opencv 示例，方便开发人员更好地了解 opencv 的使用。首先，请确保顶层 CMakeLists.txt 启用示例的构建（注意：将 REQ_EXAMPLE 设置为 ON 以启用构建）  可以从 0.beginners example 开始，然后浏览自己感兴趣的文件夹。  

​	对于维护者，可以使用 create_example.ps1 并遵循演示文件夹的名称  例如，在 powershell 中，将工作分发为 ``` ./create_example.ps1 demo ```  要快速创建演示示例。  要让演示参与构建部分，请记住将 demo_folder 名称添加到 evolve_example/examples/CMakeLists.txt 中的 EXAMPLES_LISTS 中，这用于控制哪些演示参与了构建部分。