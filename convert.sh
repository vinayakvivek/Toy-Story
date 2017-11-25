for i in ./frames/*.ppm;
do
  sips -f vertical $i
	sips -s format jpeg "$i" --out "${i%.*}.jpg";
  rm $i
done

mencoder mf://frames/*.jpg -mf fps=60:type=jpg -ovc lavc -lavcopts vcodec=mpeg4 -oac copy -o out.avi

# rm -rf frames