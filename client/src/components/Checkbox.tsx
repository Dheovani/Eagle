import { useState } from "react";

interface Props {
    id: string;
    label: string;
    onClick: (checked: boolean) => void
};

const Checkbox = (props: Props) => {
    const {
        id,
        label,
        onClick
    } = props;

    const [checked, setChecked] = useState(false);

    const onChange = () => {
        setChecked(!checked);
        onClick(!checked);
    };

    return (
        <div>
            <label htmlFor={id}>{label}</label>
            <input
                className="checkbox"
                type="checkbox"
                checked={checked}
                onChange={onChange}
                name={id}
                id={id}
            />
        </div>
    );
};

export default Checkbox;