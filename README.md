# GuitarAmpCabAndEffects
Standalone MacOS application for guitar players, which includes a speaker cabinet simulator and multiple effects pedals.

<p align="center">
<img width="1612" alt="Screenshot 2021-09-04 at 17 54 51" src="https://user-images.githubusercontent.com/90060036/132102427-a6dc429c-247c-49f7-99af-a6dcacb7f6a6.png">
</p>
The user can simply connect their guitar to the Mac through an audio interface, and will have available 7 different pedals (Overdrive, Noise Gate, Chorus, Reverb, Delay, Fuzz and Phaser). For this version, only 4 pedals can be chained at the same time but the user can set the signal chain. Additionaly, there is a selection of 4 different speaker cabinets, which are loaded as impulse responses through JUCE's Convolution Engine. The audio settings can be directly adjusted in the UI, such as I/O, sample rate and buffer size.
<br><br>
This was my first main project with the JUCE framework, and it explored most of the C++ concepts studied through a Software Development for Audio module at university. It is heavily based on an object oriented structure, which separates most of the components into differents classes that can be connected to each other, as displayed below:
<br><br>
<p align="center">
<img width="1792" alt="Screenshot 2021-09-04 at 17 52 20" src="https://user-images.githubusercontent.com/90060036/132102359-95c66f3c-47ef-421c-99ce-551a557b38f5.png">
</p>

