import Eagle from "@/assets/logo.png";
import "./styles/logo.css";

const Logo = (): JSX.Element => {
	return (
		<div className="logo">
			<img src={Eagle} alt="logo" />
		</div>
	);
};

export default Logo;