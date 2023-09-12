let index = 1;
let audioElement = new Audio("songs/1.mp3");
let masterPlay = document.getElementById("masterPlay");
let myProgressBar = document.getElementById("myProgressBar");
myProgressBar.value = 0;
let gif = document.getElementById("gif");
let songItems = Array.from(document.getElementsByClassName("songItems"));
let masterSongName = document.getElementById("masterSongName");
let pp = document.getElementById(index);

let songs = [
    {
        songName: "songName1",
        filePath: "songs/1.mp3",
        coverPath: "covers/1.jpg",
    },
    {
        songName: "songName2",
        filePath: "songs/2.mp3",
        coverPath: "covers/2.jpg",
    },
    {
        songName: "songName3",
        filePath: "songs/3.mp3",
        coverPath: "covers/3.jpg",
    },
    {
        songName: "songName4",
        filePath: "songs/4.mp3",
        coverPath: "covers/4.jpg",
    },
    {
        songName: "songName5",
        filePath: "songs/5.mp3",
        coverPath: "covers/5.jpg",
    },
    {
        songName: "songName6",
        filePath: "songs/6.mp3",
        coverPath: "covers/6.jpg",
    },
    {
        songName: "songName7",
        filePath: "songs/7.mp3",
        coverPath: "covers/7.jpg",
    },
];

songItems.forEach((element, i) => {
    element.getElementsByTagName("img")[0].src = songs[i].coverPath;
    element.getElementsByClassName("songName")[0].innerText = songs[i].songName;
});

masterPlay.addEventListener("click", () => {
    if (audioElement.paused) {
        audioElement.play();
        masterPlay.classList.remove("fa-play");
        masterPlay.classList.add("fa-pause");
        gif.style.opacity = 1;
        masterSongName.innerText = songs[index - 1].songName;

        pp = document.getElementById(index);
        if (pp) {
            pp.classList.remove("fa-play");
            pp.classList.add("fa-pause");
        }
    } else {
        audioElement.pause();
        masterPlay.classList.remove("fa-pause");
        masterPlay.classList.add("fa-play");
        gif.style.opacity = 0;
        makeAllPlay();
    }
});

myProgressBar.addEventListener("click", () => {
    audioElement.currentTime =
        (myProgressBar.value * audioElement.duration) / 100;
});

audioElement.addEventListener("timeupdate", () => {
    progress = parseInt(
        (audioElement.currentTime / audioElement.duration) * 100
    );
    myProgressBar.value = progress;
});

const makeAllPlay = () => {
    Array.from(document.getElementsByClassName("songItemPlay")).forEach(
        (element) => {
            element.classList.remove("fa-pause");
            element.classList.add("fa-play");
        }
    );
};

const makeAllPause = () => {
    Array.from(document.getElementsByClassName("songItemPlay")).forEach(
        (element) => {
            element.classList.remove("fa-play");
            element.classList.add("fa-pause");
        }
    );
};

Array.from(document.getElementsByClassName("songItemPlay")).forEach(
    (element) => {
        element.addEventListener("click", (e) => {
            if (!audioElement.paused) {
                audioElement.pause();
                masterPlay.classList.remove("fa-pause");
                masterPlay.classList.add("fa-play");
                gif.style.opacity = 0;
                makeAllPlay();
            } else {
                index = parseInt(e.target.id);
                makeAllPlay();
                e.target.classList.remove("fa-play");
                e.target.classList.add("fa-pause");
                myProgressBar.value = 0;
                audioElement.src = `songs/${index}.mp3`;
                audioElement.play();
                masterPlay.classList.remove("fa-play");
                masterPlay.classList.add("fa-pause");
                masterSongName.innerText = songs[index - 1].songName;
                gif.style.opacity = 1;
            }
        });
    }
);

document.getElementById("next").addEventListener("click", () => {
    if (index > 6) {
        index = 1;
    } else {
        index += 1;
    }
    myProgressBar.value = 0;
    audioElement.src = `songs/${index}.mp3`;
    audioElement.play();
    masterPlay.classList.remove("fa-play");
    masterPlay.classList.add("fa-pause");
    masterSongName.innerText = songs[index - 1].songName;
    makeAllPlay();
    pp = document.getElementById(index);
    if (pp) {
        pp.classList.remove("fa-play");
        pp.classList.add("fa-pause");
    }
});

document.getElementById("prev").addEventListener("click", () => {
    if (index < 1) {
        index = 7;
    } else {
        index -= 1;
    }
    myProgressBar.value = 0;
    audioElement.src = `songs/${index}.mp3`;
    audioElement.play();
    masterPlay.classList.remove("fa-play");
    masterPlay.classList.add("fa-pause");
    masterSongName.innerText = songs[index - 1].songName;
    makeAllPlay();
    pp = document.getElementById(index);
    if (pp) {
        pp.classList.remove("fa-play");
        pp.classList.add("fa-pause");
    }
});

let durations = [];
songs.forEach((song, i) => {
    let audio = new Audio(song.filePath);
    audio.addEventListener("loadedmetadata", function () {
        let durationInSeconds = audio.duration;
        let minutes = Math.floor(durationInSeconds / 60);
        let seconds = Math.floor(durationInSeconds % 60);
        let formattedDuration = `${minutes}:${seconds
            .toString()
            .padStart(2, "0")}`;
        durations[i] = formattedDuration;
        document.getElementsByClassName("timestamp")[i].innerText =
            formattedDuration;
    });
});
