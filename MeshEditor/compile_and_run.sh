make clean && clear && make &&
valgrind ./MeshEditor Cube L = 5.0, origin = \(10,10,10\), filename = "../cube.stl"
valgrind ./MeshEditor Sphere R = 2.0, origin = \(0,0,0\), filename = "../sphere.stl"
valgrind --track-origins=yes ./MeshEditor Split input = "../sphere.stl", origin = \(0,0,0\), direction = \(0,0,1\), output1 = "../split1.stl", output2 = "../split2.stl"
echo $?