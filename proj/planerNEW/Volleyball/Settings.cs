using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Volleyball
{
    class Settings
    {
        DateTime startTournament;
        int setsQualifying;
        int minutesPerSetQualifying;
        int pausePerSetQualifying;
        int pauseBetweenQualifyingInterim;
        int setsInterim;
        int minutesPerSetInterim;
        int pausePerSetInterim;
        int pauseBetweenInterimCrossgames;
        int setsCrossgames;
        int minutesPerSetCrossgame;
        int pausePerSetCrossgame;
        int pauseBetweenCrossgamesClassement;
        int setsClassement;
        int minutesPerSetClassement;
        int minutesForFinals;
        int pauseAfterFinals;
        bool useCrossgames;
        
        public Settings()
        {
            StartTournament = DateTime.Now;
            SetsQualifying = 1;
            MinutesPerSetQualifying = 10;
            PausePerSetQualifying = 0;
            PauseBetweenQualifyingInterim = 0;
            SetsInterim = 1;
            MinutesPerSetInterim = 10;
            PausePerSetInterim = 0;
            PauseBetweenInterimCrossgames = 0;
            SetsCrossgames = 1;
            MinutesPerSetCrossgame = 10;
            PausePerSetCrossgame = 0;
            PauseBetweenCrossgamesClassement = 0;
            SetsClassement = 1;
            MinutesPerSetClassement = 10;
            MinutesForFinals = 15;
            PauseAfterFinals = 30;
            UseCrossgames = true;
        }

        public DateTime StartTournament { get => startTournament; set => startTournament = value; }
        public int SetsQualifying { get => setsQualifying; set => setsQualifying = value; }
        public int MinutesPerSetQualifying { get => minutesPerSetQualifying; set => minutesPerSetQualifying = value; }
        public int PausePerSetQualifying { get => pausePerSetQualifying; set => pausePerSetQualifying = value; }
        public int PauseBetweenQualifyingInterim { get => pauseBetweenQualifyingInterim; set => pauseBetweenQualifyingInterim = value; }
        public int SetsInterim { get => setsInterim; set => setsInterim = value; }
        public int MinutesPerSetInterim { get => minutesPerSetInterim; set => minutesPerSetInterim = value; }
        public int PausePerSetInterim { get => pausePerSetInterim; set => pausePerSetInterim = value; }
        public int PauseBetweenInterimCrossgames { get => pauseBetweenInterimCrossgames; set => pauseBetweenInterimCrossgames = value; }
        public int SetsCrossgames { get => setsCrossgames; set => setsCrossgames = value; }
        public int MinutesPerSetCrossgame { get => minutesPerSetCrossgame; set => minutesPerSetCrossgame = value; }
        public int PausePerSetCrossgame { get => pausePerSetCrossgame; set => pausePerSetCrossgame = value; }
        public int PauseBetweenCrossgamesClassement { get => pauseBetweenCrossgamesClassement; set => pauseBetweenCrossgamesClassement = value; }
        public int SetsClassement { get => setsClassement; set => setsClassement = value; }
        public int MinutesPerSetClassement { get => minutesPerSetClassement; set => minutesPerSetClassement = value; }
        public int MinutesForFinals { get => minutesForFinals; set => minutesForFinals = value; }
        public int PauseAfterFinals { get => pauseAfterFinals; set => pauseAfterFinals = value; }
        public bool UseCrossgames { get => useCrossgames; set => useCrossgames = value; }
    }
}
