make clean && clear && make &&
./MeshEditor Cube L = 5.0, origin = \(0,0,0\), filename = "../cube.stl"
./MeshEditor Sphere R = 20.0, origin = \(10,10,10\), filename = "../sphere.stl"
./MeshEditor Split input = "../cube.stl", origin = \(2.5,2.5,2.5\), direction = \(1,0,0\), output1 = "../split1.stl", output2 = "../split2.stl"
echo $?